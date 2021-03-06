// Created by Michael Simms on 8/2/20.
// Copyright (c) 2020 Michael J. Simms. All rights reserved.

#ifndef __WORKOUT__
#define __WORKOUT__

#include "WorkoutType.h"
#include <string>
#include <vector>

typedef struct WorkoutInterval
{
	uint8_t m_repeat; // number of times this interval is to be repeated
	double m_duration; // duration (in seconds)
	double m_powerLow; // min power (in watts)
	double m_powerHigh; // max power (in watts)
	double m_distance; // interval distance (in meters)
	double m_pace; // interval pace (in meters/minute)
	double m_recoveryDistance; // recovery distance (in meters)
	double m_recoveryPace; // recovery pace (in meters/minute)
} WorkoutInterval;

class Workout
{
public:
	Workout();
	Workout(const std::string& workoutId, WorkoutType type, const std::string& sport);
	virtual ~Workout();

	std::string GetId() const { return m_id; };
	std::string GetSport() const { return m_sport; };
	WorkoutType GetType() const { return m_type; };
	time_t GetScheduledTime() const { return m_scheduledTime; };
	double GetEstimatedTrainingStress() const { return m_estimatedTrainingStress; };

	void SetId(const std::string& workoutId) { m_id = workoutId; };
	void SetSport(const std::string& sport) { m_sport = sport; };
	void SetType(WorkoutType type) { m_type = type; };
	void SetScheduledTime(time_t scheduledTime) { m_scheduledTime = scheduledTime; };
	void SetEstimatedStress(double estimatedStress) { m_estimatedTrainingStress = estimatedStress; };

	void AddWarmup(uint64_t seconds);
	void AddCooldown(uint64_t seconds);
	void AddInterval(uint8_t repeat, double distance, double pace, double recoveryDistance, double recoveryPace);

	double CalculateEstimatedTrainingStress(double thresholdPaceMinute);
	double CalculateDuration() const;

private:
	std::string m_id;
	std::string m_sport;
	WorkoutType m_type;
	std::vector<WorkoutInterval> m_intervals;
	time_t m_scheduledTime;
	double m_estimatedTrainingStress;

	double CalculateIntervalDuration(double intervalMeters, double intervalPaceMetersPerMinute) const;
};

#endif
