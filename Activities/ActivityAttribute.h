// Created by Michael Simms on 9/1/12.
// Copyright (c) 2012 Michael J. Simms. All rights reserved.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef __ACTIVITY_ATTRIBUTE__
#define __ACTIVITY_ATTRIBUTE__

#define ACTIVITY_ATTRIBUTE_USER_NAME                  "User Name"               // Unique identifier for the user
#define ACTIVITY_ATTRIBUTE_START_TIME                 "Start Time"              // start time (in unix time)
#define ACTIVITY_ATTRIBUTE_END_TIME                   "End Time"                // end time (in unix time)
#define ACTIVITY_ATTRIBUTE_CADENCE                    "Cadence"                 // bicycle cadence sensor reading
#define ACTIVITY_ATTRIBUTE_AVG_CADENCE                "Average Cadence"         // average bicycle cadence sensor reading
#define ACTIVITY_ATTRIBUTE_MAX_CADENCE                "Maximum Cadence"         // maximum bicycle cadence sensor reading
#define ACTIVITY_ATTRIBUTE_POWER                      "Power"                   // bicycle power meter reading
#define ACTIVITY_ATTRIBUTE_3_SEC_POWER                "3 Second Power"          // bicycle power meter reading, averaged over the last three seconds
#define ACTIVITY_ATTRIBUTE_AVG_POWER                  "Average Power"           // average bicycle power meter reading
#define ACTIVITY_ATTRIBUTE_NORMALIZED_POWER           "Normalized Power"        // normalized bicycle power meter reading
#define ACTIVITY_ATTRIBUTE_MAX_POWER                  "Maximum Power"           // maximum bicycle power meter reading
#define ACTIVITY_ATTRIBUTE_POWER_ZONE                 "Power Zone"              // current power zone
#define ACTIVITY_ATTRIBUTE_NUM_WHEEL_REVOLUTIONS      "Num. Wheel Revolutions"  // the number of wheel revolutions (from the wheel speed sensor)
#define ACTIVITY_ATTRIBUTE_WHEEL_SPEED                "Wheel Speed"             // wheel speed
#define ACTIVITY_ATTRIBUTE_REPS                       "Repetitions"             // number of repetitions (either computed or from theuser)
#define ACTIVITY_ATTRIBUTE_REPS_COMPUTED              "Repetitions (Computed)"  // number of repetitions (computed)
#define ACTIVITY_ATTRIBUTE_REPS_CORRECTED             "Repetitions (Corrected)" // number of repetitions (from the user)
#define ACTIVITY_ATTRIBUTE_SETS                       "Sets"                    // number of sets
#define ACTIVITY_ATTRIBUTE_MIN_ALTITUDE               "Minimum Altitude"        // lowest elevation
#define ACTIVITY_ATTRIBUTE_MAX_ALTITUDE               "Maximum Altitude"        // highest elevation
#define ACTIVITY_ATTRIBUTE_MOVING_TIME                "Time in Motion"          // time spent moving
#define ACTIVITY_ATTRIBUTE_AVG_PACE                   "Average Pace"            // average pace (using elapsed time)
#define ACTIVITY_ATTRIBUTE_MOVING_PACE                "Moving Pace"             // average pace (using moving time)
#define ACTIVITY_ATTRIBUTE_CURRENT_PACE               "Current Pace"            // current pace (instantaneous)
#define ACTIVITY_ATTRIBUTE_FASTEST_PACE               "Fastest Pace"            // best pace
#define ACTIVITY_ATTRIBUTE_AVG_SPEED                  "Average Speed"           // average speed (using elapsed time)
#define ACTIVITY_ATTRIBUTE_MOVING_SPEED               "Moving Speed"            // average speed (using moving time)
#define ACTIVITY_ATTRIBUTE_CURRENT_SPEED              "Current Speed"           // current speed (instantaneous)
#define ACTIVITY_ATTRIBUTE_FASTEST_SPEED              "Fastest Speed"           // best speed
#define ACTIVITY_ATTRIBUTE_DISTANCE_TRAVELED          "Distance"                // total distance traveled
#define ACTIVITY_ATTRIBUTE_PREVIOUS_DISTANCE_TRAVELED "Previous Distance"       // total distance traveled (second most recent value)
#define ACTIVITY_ATTRIBUTE_STEPS_TAKEN                "Steps Taken"             // number of foot strikes
#define ACTIVITY_ATTRIBUTE_HEART_RATE                 "Heart Rate"              // current heart rate (bpm)
#define ACTIVITY_ATTRIBUTE_AVG_HEART_RATE             "Average Heart Rate"      // average heart rate (bpm)
#define ACTIVITY_ATTRIBUTE_MAX_HEART_RATE             "Maximum Heart Rate"      // highest heart rate (bpm)
#define ACTIVITY_ATTRIBUTE_HEART_RATE_PERCENTAGE      "Heart Rate Percentage"   // % of maximum heart rate
#define ACTIVITY_ATTRIBUTE_HEART_RATE_ZONE            "Heart Rate Zone"         // % of maximum heart rate, as a zone
#define ACTIVITY_ATTRIBUTE_ELAPSED_TIME               "Elapsed Time"            // total elapsed time
#define ACTIVITY_ATTRIBUTE_LATITUDE                   "Latitude"                // current latitude
#define ACTIVITY_ATTRIBUTE_LONGITUDE                  "Longitude"               // current longitude
#define ACTIVITY_ATTRIBUTE_ALTITUDE                   "Altitude"                // current altitude
#define ACTIVITY_ATTRIBUTE_HORIZONTAL_ACCURACY        "Horizontal Accuracy"     // horizontal accuracy, in meters
#define ACTIVITY_ATTRIBUTE_VERTICAL_ACCURACY          "Vertical Accuracy"       // vertical accuracy, in meters
#define ACTIVITY_ATTRIBUTE_STARTING_LATITUDE          "Starting Latitude"       // initial latitude
#define ACTIVITY_ATTRIBUTE_STARTING_LONGITUDE         "Starting Longitude"      // initial longitude
#define ACTIVITY_ATTRIBUTE_X                          "X"                       // current acceleromter value
#define ACTIVITY_ATTRIBUTE_Y                          "Y"                       // current acceleromter value
#define ACTIVITY_ATTRIBUTE_Z                          "Z"                       // current acceleromter value
#define ACTIVITY_ATTRIBUTE_FASTEST_CENTURY            "Fastest Century"         // best 100 miles
#define ACTIVITY_ATTRIBUTE_FASTEST_METRIC_CENTURY     "Fastest Metric Century"  // best 100 K
#define ACTIVITY_ATTRIBUTE_FASTEST_MARATHON           "Fastest Marathon"        // best 26.2 miles
#define ACTIVITY_ATTRIBUTE_FASTEST_HALF_MARATHON      "Fastest Half Marathon"   // best 13.1 miles
#define ACTIVITY_ATTRIBUTE_FASTEST_10K                "Fastest 10K"             // best 10K
#define ACTIVITY_ATTRIBUTE_FASTEST_5K                 "Fastest 5K"              // best 5K
#define ACTIVITY_ATTRIBUTE_FASTEST_MILE               "Fastest Mile"            // best mile
#define ACTIVITY_ATTRIBUTE_FASTEST_KM                 "Fastest Km"              // best km
#define ACTIVITY_ATTRIBUTE_FASTEST_400M               "Fastest 400M"            // best 400 meters
#define ACTIVITY_ATTRIBUTE_LAST_10K                   "Last 10K"                // most recent 10K
#define ACTIVITY_ATTRIBUTE_LAST_5K                    "Last 5K"                 // most recent 5K
#define ACTIVITY_ATTRIBUTE_LAST_MILE                  "Last Mile"               // most recent mile
#define ACTIVITY_ATTRIBUTE_LAST_KM                    "Last Km"                 // most recent km
#define ACTIVITY_ATTRIBUTE_CURRENT_CLIMB              "Current Climb"           // current climb (M)
#define ACTIVITY_ATTRIBUTE_BIGGEST_CLIMB              "Biggest Climb"           // biggest climb (M)
#define ACTIVITY_ATTRIBUTE_VERTICAL_SPEED             "Vertical Speed"          // Vm/h
#define ACTIVITY_ATTRIBUTE_CALORIES_BURNED            "Calories"                // total calories burned
#define ACTIVITY_ATTRIBUTE_SPLIT_TIME                 "Split Time "             // "Split Time KM 1", "Split Time Mile 1", etc.
#define ACTIVITY_ATTRIBUTE_LAP_TIME                   "Lap Time "               // "Lap Time 1", etc.
#define ACTIVITY_ATTRIBUTE_GRAPH_PEAK                 "Graph Peak "             // "Graph Peak 1", etc.
#define ACTIVITY_ATTRIBUTE_CURRENT_LAP_TIME           "Current Lap Time"        //
#define ACTIVITY_ATTRIBUTE_ADDITIONAL_WEIGHT          "Additional Weight"       // weight, in kg (such as barbells, etc.)
#define ACTIVITY_ATTRIBUTE_RUN_STRIDE_LENGTH          "Run Stride Length"       // stride length from a foot pod
#define ACTIVITY_ATTRIBUTE_RUN_DISTANCE               "Run Distance"            // distance from a foot pod
#define ACTIVITY_ATTRIBUTE_TOTAL_ASCENT               "Total Ascent"            // 
#define ACTIVITY_ATTRIBUTE_SWIM_STROKES               "Swim Strokes"            // the number of swim strokes taken

#endif
