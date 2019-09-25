//  Created by Michael Simms on 9/16/19.
//  Copyright © 2019 Michael J Simms Software. All rights reserved.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#import "DetailsViewController.h"
#import "ExtensionDelegate.h"
#import "ActivityMgr.h"

@implementation DetailsRowController

@synthesize itemLabel;

@end


@interface DetailsViewController ()

@end


@implementation DetailsViewController

@synthesize map;
@synthesize detailsTable;

- (instancetype)init
{
	self = [super init];
	if (self)
	{
	}
	return self;
}

- (void)willActivate
{
	[super willActivate];
}

- (void)didDeactivate
{
	[super didDeactivate];
}

- (void)awakeWithContext:(id)context
{
	[super awakeWithContext:context];
}

#pragma mark accessor methods

- (void)setActivityIndex:(NSInteger)index
{
	self->activityIndex = index;

	CreateHistoricalActivityObject(index);
	LoadHistoricalActivitySummaryData(index);
}

#pragma mark location handling methods

- (void)redraw
{	
	ExtensionDelegate* extDelegate = [WKExtension sharedExtension].delegate;
	if (extDelegate && [extDelegate loadHistoricalActivity:self->activityIndex])
	{
		self->attributeNames = [[NSMutableArray alloc] init];
		self->recordNames = [[NSMutableArray alloc] init];

		self->activityId = [[NSString alloc] initWithFormat:@"%s", ConvertActivityIndexToActivityId(self->activityIndex)];
		GetHistoricalActivityStartAndEndTime(self->activityIndex, &self->startTime, &self->endTime);
	}
}

@end