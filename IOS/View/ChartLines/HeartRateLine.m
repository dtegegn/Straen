// Created by Michael Simms on 2/25/13.
// Copyright (c) 2013 Michael J. Simms. All rights reserved.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#import "HeartRateLine.h"
#import "ActivityAttribute.h"
#import "AppDelegate.h"
#import "ChartPoint.h"

@interface HeartRateLine ()

@end

@implementation HeartRateLine

void HeartRateDataCallback(const char* const activityId, void* context)
{
	HeartRateLine* ptrToHeartRateChart = (__bridge HeartRateLine*)context;

	AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
	ActivityAttributeType hrValue = [appDelegate queryHistoricalActivityAttribute:ACTIVITY_ATTRIBUTE_HEART_RATE forActivityId:[NSString stringWithUTF8String:activityId]];

	if (hrValue.valid)
	{
		NSNumber* x = [[NSNumber alloc] initWithUnsignedInteger:[ptrToHeartRateChart->points count]];
		NSNumber* y = [[NSNumber alloc] initWithDouble:hrValue.value.doubleVal];

		ChartPoint* point = [[ChartPoint alloc] initWithValues:x :y];
		if (point)
		{
			[ptrToHeartRateChart->points addObject:point];
		}
	}
}

- (void)draw
{
	self->points = [[NSMutableArray alloc] init];
	if (self->points)
	{
		AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
		[appDelegate createHistoricalActivityObject:self->activityId];

		if ([appDelegate loadHistoricalActivitySensorData:SENSOR_TYPE_HEART_RATE forActivityId:self->activityId withCallback:HeartRateDataCallback withContext:(__bridge void*)self])
		{
			[super draw];
		}
	}
}

@end
