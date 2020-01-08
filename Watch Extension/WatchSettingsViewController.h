//  Created by Michael Simms on 7/15/19.
//  Copyright © 2019 Michael J Simms Software. All rights reserved.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#import <WatchKit/WatchKit.h>
#import <Foundation/Foundation.h>

@interface WatchSettingsViewController : WKInterfaceController
{
	IBOutlet __strong WKInterfaceSwitch* broadcast;
	IBOutlet __strong WKInterfaceButton* resetButton;
}

@property (nonatomic, retain) IBOutlet WKInterfaceSwitch* broadcast;
@property (nonatomic, retain) IBOutlet WKInterfaceButton* resetButton;

@end
