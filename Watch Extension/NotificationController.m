//  Created by Michael Simms on 6/12/19.
//  Copyright © 2019 Michael J Simms Software. All rights reserved.

#import "NotificationController.h"


@interface NotificationController ()

@end


@implementation NotificationController

- (instancetype)init {
	self = [super init];
	if (self)
	{
	}
	return self;
}

- (void)willActivate {
	// This method is called when watch view controller is about to be visible to user
	[super willActivate];
}

- (void)didDeactivate {
	// This method is called when watch view controller is no longer visible
	[super didDeactivate];
}

- (void)didReceiveNotification:(UNNotification *)notification {
	// This method is called when a notification needs to be presented.
	// Implement it if you use a dynamic notification interface.
	// Populate your dynamic notification interface as quickly as possible.
}

@end