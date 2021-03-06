// Created by Michael Simms on 9/9/12.
// Copyright (c) 2012 Michael J. Simms. All rights reserved.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#import "CommonViewController.h"
#import "ActivityPreferences.h"
#import "Segues.h"
#import "ActivityMgr.h"

#define ACTIVITY_BUTTON_AUTOSTART NSLocalizedString(@"Autostart", nil)
#define ACTIVITY_BUTTON_START     NSLocalizedString(@"Start", nil)
#define ACTIVITY_BUTTON_STOP      NSLocalizedString(@"Stop", nil)
#define ACTIVITY_BUTTON_PAUSE     NSLocalizedString(@"Pause", nil)
#define ACTIVITY_BUTTON_RESUME    NSLocalizedString(@"Resume", nil)

@interface ActivityViewController : CommonViewController <UIActionSheetDelegate, UIGestureRecognizerDelegate>
{
	IBOutlet UINavigationItem* navItem;
	IBOutlet UIToolbar*        toolbar;
	IBOutlet UILabel*          messagesLabel;
	IBOutlet UIBarButtonItem*  moreButton;
	IBOutlet UIBarButtonItem*  customizeButton;
	IBOutlet UIBarButtonItem*  bikeButton;
	IBOutlet UIBarButtonItem*  intervalsButton;
	IBOutlet UIBarButtonItem*  paceButton;
	IBOutlet UIBarButtonItem*  lapButton;
	IBOutlet UIBarButtonItem*  autoStartButton;
	IBOutlet UIBarButtonItem*  startStopButton;
	IBOutlet UIBarButtonItem*  weightButton;

	uint8_t                    countdownSecs;
	NSTimer*                   countdownTimer;
	NSTimer*                   refreshTimer;
	NSInteger                  screenHeight;
	UIImageView*               lastCountdownImage;
	NSMutableArray*            attributesToDisplay;
	NSMutableArray*            valueLabels;
	NSMutableArray*            titleLabels;
	NSMutableArray*            unitsLabels;
	NSMutableArray*            messages;
	uint8_t                    messageDisplayCounter;
	uint8_t                    numAttributes;
	double                     lastHeartRateValue;
	double                     lastCadenceValue;
	double                     lastPowerValue;
	ActivityPreferences*       activityPrefs;
	NSString*                  bikeName;
	bool                       autoStartCoordinateSet;
	Coordinate                 autoStartCoordinate;
	NSInteger                  tappedButtonIndex;
}

- (void)onRefreshTimer:(NSTimer*)timer;
- (void)startTimer;
- (void)stopTimer;

- (void)initializeLabelText;
- (void)initializeLabelColor;

- (void)addTapGestureRecognizersToAllLabels;

- (void)playBeepSound;
- (void)playPingSound;

- (void)setUIForStartedActivity;
- (void)setUIForStoppedActivity;
- (void)setUIForPausedActivity;
- (void)setUIForResumedActivity;

- (void)doStart;
- (void)doStop;
- (void)doPause;

- (void)refreshScreen;

- (IBAction)onAutoStart:(id)sender;
- (IBAction)onStartStop:(id)sender;
- (IBAction)onWeight:(id)sender;
- (IBAction)onLap:(id)sender;
- (IBAction)onCustomize:(id)sender;
- (IBAction)onBike:(id)sender;
- (IBAction)onIntervals:(id)sender;
- (IBAction)onPace:(id)sender;
- (IBAction)onSummary:(id)sender;

- (void)locationUpdated:(NSNotification*)notification;

@property (nonatomic, retain) IBOutlet UINavigationItem* navItem;
@property (nonatomic, retain) IBOutlet UIToolbar*        toolbar;
@property (nonatomic, retain) IBOutlet UILabel*          messagesLabel;
@property (nonatomic, retain) IBOutlet UIBarButtonItem*  moreButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem*  customizeButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem*  bikeButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem*  intervalsButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem*  paceButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem*  lapButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem*  autoStartButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem*  startStopButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem*  weightButton;

@end
