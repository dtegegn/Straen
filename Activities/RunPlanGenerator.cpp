// Created by Michael Simms on 8/3/20.
// Copyright (c) 2020 Michael J. Simms. All rights reserved.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "RunPlanGenerator.h"
#include "ActivityAttribute.h"
#include "ActivitySummary.h"
#include "ExperienceLevel.h"
#include "GoalType.h"
#include "WorkoutFactory.h"
#include "WorkoutPlanInputs.h"

#include <math.h>
#include <random>

RunPlanGenerator::RunPlanGenerator()
{
}

RunPlanGenerator::~RunPlanGenerator()
{
}

bool RunPlanGenerator::ValidFloat(double num, double minValue)
{
	return num > minValue;
}

double RunPlanGenerator::RoundDistance(double distance)
{
	return float(ceil(distance / 100.0)) * 100.0;
}

// Given a distance, returns the nearest 'common' interval distance,
// i.e., if given 407 meters, returns 400 meters, because no one runs 407 meter intervals.
uint64_t RunPlanGenerator::NearestIntervalDistance(double distance, double minDistanceInMeters)
{
	if (distance < minDistanceInMeters)
		distance = minDistanceInMeters;

	uint64_t METRIC_INTERVALS[] = { 400, 800, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 12000, 15000, 20000, 21000, 25000 };
	//double US_CUSTOMARY_INTERVALS[] { 0.25, 0.5, 1.0, 1.5, 2.0, 3.0, 3.1, 5.0, 6.0, 6.2, 8.0, 10.0, 12.0, 13.1 };

	size_t numIntervals = sizeof(METRIC_INTERVALS) / sizeof(uint64_t);
	uint64_t lastInterval = 0;

	for (size_t i = 0; i < numIntervals - 1; ++i)
	{
		uint64_t currentInterval = METRIC_INTERVALS[i];

		if (currentInterval > distance)
		{
			if ((lastInterval > 0) &&  (currentInterval - distance > distance - lastInterval))
			{
				return lastInterval;
			}
			return currentInterval;
		}
		lastInterval = currentInterval;
	}
	return METRIC_INTERVALS[numIntervals - 1];
}

// Utility function for creating an easy run of some random distance between min and max.
Workout* RunPlanGenerator::GenerateEasyRun(double pace, uint64_t minRunDistance, uint64_t maxRunDistance)
{
	// An easy run needs to be at least a couple of kilometers.
	if (minRunDistance < 2000)
		minRunDistance = 2000;
	if (maxRunDistance < 2000)
		maxRunDistance = 2000;

	// Roll the dice to figure out the distance.
	std::default_random_engine generator;
	std::uniform_int_distribution<uint64_t> distribution(minRunDistance, maxRunDistance);
	uint64_t runDistance = distribution(generator);
	uint64_t intervalDistanceMeters = (runDistance / 10) * 10;

	// Create the workout object.
	Workout* easyRunWorkout = WorkoutFactory::Create(WORKOUT_TYPE_EASY_RUN, ACTIVITY_TYPE_RUNNING);
	if (easyRunWorkout)
	{
		easyRunWorkout->AddInterval(1, intervalDistanceMeters, pace, 0, 0);

		// Tally up the easy and hard distance so we can keep the weekly plan in check.
		this->m_easyDistanceTotalMeters += intervalDistanceMeters;
	}

	return easyRunWorkout;
}

// Utility function for creating a tempo workout.
Workout* RunPlanGenerator::GenerateTempoRun(double tempoRunPace, double easyRunPace, uint64_t maxRunDistance)
{
	double tempDistance = 30.0 * tempoRunPace;
	uint64_t intervalDistanceMeters = RunPlanGenerator::NearestIntervalDistance(tempDistance, 2000.0);

	// Sanity check.
	if (intervalDistanceMeters > maxRunDistance)
		intervalDistanceMeters = maxRunDistance;
	if (intervalDistanceMeters < 1000)
		intervalDistanceMeters = 1000;

	uint64_t warmupDuration = 10 * 60;
	uint64_t cooldownDuration = 10 * 60;

	// Create the workout object.
	Workout* tempoRunWorkout = WorkoutFactory::Create(WORKOUT_TYPE_TEMPO_RUN, ACTIVITY_TYPE_RUNNING);
	tempoRunWorkout->AddWarmup(warmupDuration);
	tempoRunWorkout->AddInterval(1, intervalDistanceMeters, tempoRunPace, 0, 0);
	tempoRunWorkout->AddCooldown(cooldownDuration);

	// Tally up the easy and hard distance so we can keep the weekly plan in check.
	this->m_easyDistanceTotalMeters += (warmupDuration / easyRunPace);
	this->m_easyDistanceTotalMeters += (cooldownDuration / easyRunPace);
	this->m_hardDistanceTotalMeters += intervalDistanceMeters;

	return tempoRunWorkout;
}

// Utility function for creating a speed/interval workout.
Workout* RunPlanGenerator::GenerateSpeedRun(double shortIntervalRunPace, double speedRunPace, double easyRunPace, double goalDistance)
{
	// Constants.
	const uint8_t MIN_REPS_INDEX = 0;
	const uint8_t MAX_REPS_INDEX = 1;
	const uint8_t REP_DISTANCE_INDEX = 2;
	const uint8_t NUM_POSSIBLE_WORKOUTS = 7;

	// Build a collection of possible run interval sessions, sorted by target distance. Order is { min reps, max reps, distance in meters }.
	uint16_t POSSIBLE_WORKOUTS[NUM_POSSIBLE_WORKOUTS][3] = { { 4, 8, 100 }, { 4, 8, 200 }, { 4, 8, 400 }, { 4, 6, 600 }, { 2, 4, 800 }, { 2, 4, 1000 }, { 2, 4, 1600 } };

	uint64_t warmupDuration = 10 * 60;
	uint64_t cooldownDuration = 10 * 60;

	std::default_random_engine generator;

	// Select the workout.
	std::normal_distribution<size_t> workoutDistribution(0, NUM_POSSIBLE_WORKOUTS - 1);
	size_t selectedIntervalWorkoutIndex = workoutDistribution(generator);
	uint16_t* selectedIntervalWorkout = POSSIBLE_WORKOUTS[selectedIntervalWorkoutIndex];

	// Determine the pace for this workout.
	double intervalPace;
	if (selectedIntervalWorkout[REP_DISTANCE_INDEX] < 1000)
		intervalPace = shortIntervalRunPace;
	else
		intervalPace = speedRunPace;

	// Determine the number of reps for this workout.
	std::uniform_int_distribution<uint16_t> repsDistribution(selectedIntervalWorkout[MIN_REPS_INDEX], selectedIntervalWorkout[MAX_REPS_INDEX]);
	uint16_t selectedReps = repsDistribution(generator);

	// Determine the distance for this workout.
	uint16_t intervalDistance = selectedIntervalWorkout[REP_DISTANCE_INDEX];
	uint16_t restIntervalDistance = intervalDistance * 2;

	// Create the workout object.
	Workout* intervalRunWorkout = WorkoutFactory::Create(WORKOUT_TYPE_SPEED_RUN, ACTIVITY_TYPE_RUNNING);
	intervalRunWorkout->AddWarmup(warmupDuration);
	intervalRunWorkout->AddInterval(selectedReps, intervalDistance, intervalPace, restIntervalDistance, easyRunPace);
	intervalRunWorkout->AddCooldown(cooldownDuration);

	// Tally up the easy and hard distance so we can keep the weekly plan in check.
	this->m_easyDistanceTotalMeters += (warmupDuration / easyRunPace);
	this->m_easyDistanceTotalMeters += (cooldownDuration / easyRunPace);
	this->m_easyDistanceTotalMeters += ((selectedReps - 1) * restIntervalDistance);
	this->m_hardDistanceTotalMeters += (selectedReps * intervalDistance);

	return intervalRunWorkout;
}

// Utility function for creating a long run workout.
Workout* RunPlanGenerator::GenerateLongRun(double longRunPace, double longestRunInFourWeeks, double minRunDistance, double maxRunDistance)
{
	// Long run should be 10% longer than the previous long run, within the bounds provided by min and max.
	double longRunDistance = longestRunInFourWeeks * 1.1;
	if (longRunDistance > minRunDistance)
		longRunDistance = minRunDistance;
	if (longRunDistance < minRunDistance)
		longRunDistance = minRunDistance;
	double intervalDistanceMeters = RunPlanGenerator::RoundDistance(longRunDistance);

	// Create the workout object.
	Workout* longRunWorkout = WorkoutFactory::Create(WORKOUT_TYPE_LONG_RUN, ACTIVITY_TYPE_RUNNING);
	longRunWorkout->AddInterval(1, intervalDistanceMeters, longRunPace, 0, 0);

	// Tally up the easy and hard distance so we can keep the weekly plan in check.
	this->m_easyDistanceTotalMeters += intervalDistanceMeters;

	return longRunWorkout;
}

// Utility function for creating a free run workout.
Workout* RunPlanGenerator::GenerateFreeRun(void)
{
	// Create the workout object.
	Workout* longRunWorkout = WorkoutFactory::Create(WORKOUT_TYPE_FREE_RUN, ACTIVITY_TYPE_RUNNING);
	longRunWorkout->AddInterval(1, 5000, 0, 0, 0);

	return longRunWorkout;
}

std::vector<Workout*> RunPlanGenerator::GenerateWorkouts(std::map<std::string, double>& inputs)
{
	std::vector<Workout*> workouts;

	// 3 Critical runs: Speed session, tempo run, and long run

	double goalDistance = inputs.at(WORKOUT_INPUT_GOAL_RUN_DISTANCE);
	double goalType = inputs.at(WORKOUT_INPUT_GOAL_TYPE);
	double shortIntervalRunPace = inputs.at(WORKOUT_INPUT_SHORT_INTERVAL_RUN_PACE);
	double functionalThresholdPace = inputs.at(WORKOUT_INPUT_FUNCTIONAL_THRESHOLD_PACE);
	double speedRunPace = inputs.at(WORKOUT_INPUT_SPEED_RUN_PACE);
	double tempoRunPace = inputs.at(WORKOUT_INPUT_TEMPO_RUN_PACE);
	double longRunPace = inputs.at(WORKOUT_INPUT_LONG_RUN_PACE);
	double easyRunPace = inputs.at(WORKOUT_INPUT_EASY_RUN_PACE);
	double longestRunInFourWeeks = inputs.at(WORKOUT_INPUT_LONGEST_RUN_IN_FOUR_WEEKS);
	double longestRunWeek1 = inputs.at(WORKOUT_INPUT_LONGEST_RUN_WEEK_1);
	double longestRunWeek2 = inputs.at(WORKOUT_INPUT_LONGEST_RUN_WEEK_2);
	double longestRunWeek3 = inputs.at(WORKOUT_INPUT_LONGEST_RUN_WEEK_3);
	//double inTaper = inputs.at(WORKOUT_INPUT_IN_TAPER);
	double avgRunDistance = inputs.at(WORKOUT_INPUT_AVG_RUNNING_DISTANCE_IN_FOUR_WEEKS);
	double expLevel = inputs.at(WORKOUT_INPUT_EXPERIENCE_LEVEL);

	// Handle situation in which the user hasn't run in four weeks.
	if (!RunPlanGenerator::ValidFloat(longestRunInFourWeeks, 100.0))
	{
		workouts.push_back(this->GenerateFreeRun());
		workouts.push_back(this->GenerateFreeRun());
		return workouts;
	}

	// No pace data?
	if (!(RunPlanGenerator::ValidFloat(shortIntervalRunPace, 0.1) && RunPlanGenerator::ValidFloat(speedRunPace, 0.1) && RunPlanGenerator::ValidFloat(tempoRunPace, 0.1) && RunPlanGenerator::ValidFloat(longRunPace, 0.1) && RunPlanGenerator::ValidFloat(easyRunPace, 0.1)))
	{
		return workouts;
	}

	// If the long run has been increasing for the last three weeks then give the person a break.
	if (RunPlanGenerator::ValidFloat(longestRunWeek1, 0.1) && RunPlanGenerator::ValidFloat(longestRunWeek2, 0.1) && RunPlanGenerator::ValidFloat(longestRunWeek3, 0.1))
	{
		if (longestRunWeek1 >= longestRunWeek2 && longestRunWeek2 >= longestRunWeek3)
			longestRunInFourWeeks *= 0.75;
	}

	// Compute the longest run needed to accomplish the goal.
	// If the goal distance is a marathon then the longest run should be somewhere between 18 and 22 miles.
	// This equation was derived by playing with trendlines in a spreadsheet.
	double maxLongRunDistance = ((-0.002 * goalDistance) *  (-0.002 * goalDistance)) + (0.7 * goalDistance) + 4.4;

	// Handle situation in which the user is already meeting or exceeding the goal distance.
	if (longestRunInFourWeeks >= maxLongRunDistance)
	{
		longestRunInFourWeeks = maxLongRunDistance;
	}

	// Distance ceilings for easy and tempo runs.
	double maxEasyRunDistance;
	double maxTempoRunDistance;
	if (expLevel == EXPERIENCE_LEVEL_BEGINNER)
	{
		maxEasyRunDistance = longestRunInFourWeeks * 0.60;
		maxTempoRunDistance = longestRunInFourWeeks * 0.40;
	}
	else
	{
		maxEasyRunDistance = longestRunInFourWeeks * 0.75;
		maxTempoRunDistance = longestRunInFourWeeks * 0.50;
	}

	// Don't make any runs (other than intervals, tempo runs, etc.) shorter than this.
	double minRunDistance = avgRunDistance * 0.5;
	if (minRunDistance > maxEasyRunDistance)
		minRunDistance = maxEasyRunDistance;

	// We'll also set the percentage of easy miles/kms based on the experience level.
	double minEasyDistancePercentage;
	if (expLevel == EXPERIENCE_LEVEL_BEGINNER)
		minEasyDistancePercentage = 0.90;
	else if (expLevel == EXPERIENCE_LEVEL_INTERMEDIATE)
		minEasyDistancePercentage = 0.80;
	else
		minEasyDistancePercentage = 0.75;

	size_t iterCount = 0;
	bool done = false;
	while (!done)
	{
		// Keep track of the number of easy miles/kms and the number of hard miles/kms we're expecting the user to run so we can balance the two.
		this->m_easyDistanceTotalMeters = 0.0;
		this->m_hardDistanceTotalMeters = 0.0;

		// Add a long run.
		Workout* longRunWorkout = this->GenerateLongRun(longRunPace, longestRunInFourWeeks, minRunDistance, maxLongRunDistance);
		workouts.push_back(longRunWorkout);

		// Add an easy run.
		Workout* easyRunWorkout = this->GenerateEasyRun(easyRunPace, minRunDistance, maxEasyRunDistance);
		workouts.push_back(easyRunWorkout);

		// Add a tempo run. Run should be 20-30 minutes in duration.
		Workout* tempoRunWorkout = this->GenerateTempoRun(tempoRunPace, easyRunPace, maxTempoRunDistance);
		workouts.push_back(tempoRunWorkout);

		// The user cares about speed as well as completing the distance. Also note that we should add strikes to one of the other workouts.
		if (goalType == GOAL_TYPE_SPEED)
		{
			// Add an interval/speed session.
			Workout* intervalWorkout = this->GenerateSpeedRun(shortIntervalRunPace, speedRunPace, easyRunPace, goalDistance);
			workouts.push_back(intervalWorkout);
		}

		// Add an easy run.
		easyRunWorkout = this->GenerateEasyRun(easyRunPace, minRunDistance, maxEasyRunDistance);
		workouts.push_back(easyRunWorkout);

		// Keep track of the total distance as well as the easy distance to keep from planning too many intense miles/kms.
		double totalDistance = this->m_easyDistanceTotalMeters + this->m_hardDistanceTotalMeters;
		double easyDistancePercentage = this->m_easyDistanceTotalMeters / totalDistance;

		// This is used to make sure we don't loop forever.
		iterCount = iterCount + 1;

		// Exit conditions:
		if (iterCount >= 6)
			done = true;
		if (easyDistancePercentage >= minEasyDistancePercentage)
			done = true;
	}

	// Calculate the total stress for each workout.
	for (auto workoutIter = workouts.begin(); workoutIter != workouts.end(); ++workoutIter)
	{
		(*workoutIter)->CalculateEstimatedTrainingStress(functionalThresholdPace);
	}

	return workouts;
}
