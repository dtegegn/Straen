// Created by Michael Simms on 3/3/13.
// Copyright (c) 2013 Michael J. Simms. All rights reserved.

// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#import "ProfileViewController.h"
#import "AppDelegate.h"
#import "AppStrings.h"
#import "DateViewController.h"
#import "Segues.h"
#import "StringUtils.h"

typedef enum ProfileSections
{
	SECTION_USER = 0,
	SECTION_PERFORMANCE,
	NUM_PROFILE_SECTIONS
} ProfileSections;

typedef enum ProfileUserRows
{
	ROW_GENDER = 0,
	ROW_BIRTHDATE,
	ROW_HEIGHT,
	ROW_WEIGHT,
	NUM_PROFILE_USER_ROWS
} ProfileUserRows;

typedef enum ProfilePerformanceRows
{
	ROW_ACTIVITY_LEVEL = 0,
	ROW_FTP,
	NUM_PROFILE_PERFORMANCE_ROWS
} ProfilePerformanceRows;

#define TITLE                             NSLocalizedString(@"Profile", nil)

#define TITLE_USER                        NSLocalizedString(@"Profile", nil)
#define TITLE_PERFORMANCE                 NSLocalizedString(@"Activity Level", nil)

#define ACTION_SHEET_TITLE_ACTIVITY_LEVEL NSLocalizedString(@"Activity Level", nil)
#define ACTION_SHEET_TITLE_BIRTHDATE      NSLocalizedString(@"Enter your birthdate", nil)
#define ALERT_MSG_HEIGHT                  NSLocalizedString(@"Please enter your height", nil)
#define ALERT_MSG_WEIGHT                  NSLocalizedString(@"Please enter your weight", nil)
#define ALERT_MSG_FTP                     NSLocalizedString(@"Please enter your FTP", nil)
#define TITLE_BIRTHDATE                   NSLocalizedString(@"Birthdate", nil)

@interface ProfileViewController ()

@end

@implementation ProfileViewController

@synthesize profileTableView;
@synthesize toolbar;

- (id)initWithNibName:(NSString*)nibNameOrNil bundle:(NSBundle*)nibBundleOrNil
{
	self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
	return self;
}

- (void)viewDidLoad
{
	self.title = TITLE;

	[super viewDidLoad];
	[self.navigationController.navigationBar setTintColor:[UIColor blackColor]];
	[self.toolbar setTintColor:[UIColor blackColor]];
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewDidAppear:animated];

	if (self->dateVC)
	{
		AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
		NSDate* dateObj = [[self->dateVC datePicker] date];
		[appDelegate setUserBirthDate:dateObj];
		self->dateVC = NULL;
	}

	[super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
	[super viewDidAppear:animated];
	[self.navigationController.navigationBar setTintColor:[UIColor blackColor]];
	[self.toolbar setTintColor:[UIColor blackColor]];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotate
{
	return YES;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations
{
	return UIInterfaceOrientationMaskPortrait | UIInterfaceOrientationMaskLandscapeLeft | UIInterfaceOrientationMaskLandscapeRight;
}

- (void)deviceOrientationDidChange:(NSNotification*)notification
{
}

- (void)prepareForSegue:(UIStoryboardSegue*)segue sender:(id)sender
{
	AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
	NSString* segueId = [segue identifier];

	if ([segueId isEqualToString:@SEGUE_TO_DATE_VIEW])
	{
		self->dateVC = (DateViewController*)[segue destinationViewController];
		if (self->dateVC)
		{
			struct tm dateStruct = [appDelegate userBirthDate];
			NSDate* dateObj = [[NSDate alloc] initWithTimeIntervalSince1970:mktime(&dateStruct)];
			[self->dateVC setInitialValue:dateObj];
		}
	}
}

#pragma mark UITableView methods

- (NSInteger)numberOfSectionsInTableView:(UITableView*)tableView
{
	return NUM_PROFILE_SECTIONS;
}

- (NSString*)tableView:(UITableView*)tableView titleForHeaderInSection:(NSInteger)section
{
	switch (section)
	{
		case SECTION_USER:
			return TITLE_USER;
		case SECTION_PERFORMANCE:
			return TITLE_PERFORMANCE;
	}
	return @"";
}

- (NSInteger)tableView:(UITableView*)tableView numberOfRowsInSection:(NSInteger)section
{
	switch (section)
	{
		case SECTION_USER:
			return NUM_PROFILE_USER_ROWS;
		case SECTION_PERFORMANCE:
			return NUM_PROFILE_PERFORMANCE_ROWS;
	}
	return 0;
}

- (UITableViewCell*)tableView:(UITableView*)tableView cellForRowAtIndexPath:(NSIndexPath*)indexPath
{
	static NSString* CellIdentifier = @"Cell";

	UITableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
	if (cell == nil)
	{
		cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue2 reuseIdentifier:CellIdentifier];
	}

	NSInteger section = [indexPath section];
	NSInteger row = [indexPath row];

	AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];

	switch (section)
	{
		case SECTION_USER:
			{
				switch (row)
				{
					case ROW_GENDER:
						cell.textLabel.text = STR_GENDER;
						cell.detailTextLabel.text = [StringUtils genderToStr:[appDelegate userGender]];
						break;
					case ROW_BIRTHDATE:
						{
							struct tm birthDate = [appDelegate userBirthDate];
							cell.textLabel.text = TITLE_BIRTHDATE;
							cell.detailTextLabel.text = [StringUtils formatDateFromTimeStruct:&birthDate];
						}
						break;
					case ROW_HEIGHT:
						{
							double height = [appDelegate userHeight];
							cell.textLabel.text = STR_HEIGHT;
							cell.detailTextLabel.text = [[NSString alloc] initWithFormat:@"%0.1f %@", height, [StringUtils formatActivityMeasureType:MEASURE_HEIGHT]];
						}
						break;
					case ROW_WEIGHT:
						{
							double weight = [appDelegate userWeight];
							cell.textLabel.text = STR_WEIGHT;
							cell.detailTextLabel.text = [[NSString alloc] initWithFormat:@"%0.1f %@", weight, [StringUtils formatActivityMeasureType:MEASURE_WEIGHT]];
						}
						break;
					default:
						break;
				}
			}
			break;
		case SECTION_PERFORMANCE:
			{
				switch (row)
				{
					case ROW_ACTIVITY_LEVEL:
						cell.textLabel.text = ACTION_SHEET_TITLE_ACTIVITY_LEVEL;
						cell.detailTextLabel.text = [StringUtils activityLevelToStr:[appDelegate userActivityLevel]];
						break;
					case ROW_FTP:
						{
							double declaredFtp = [appDelegate userSpecifiedFtp];
							cell.textLabel.text = STR_FTP;

							if (declaredFtp >= (double)1.0)
							{
								cell.detailTextLabel.text = [[NSString alloc] initWithFormat:@"%0.0f %@", declaredFtp, [StringUtils formatActivityMeasureType:MEASURE_POWER]];
							}
							else
							{
								double estimatedFtp = [appDelegate userEstimatedFtp];

								if (estimatedFtp >= (double)1.0)
									cell.detailTextLabel.text = [[NSString alloc] initWithFormat:@"%0.0f %@ (Estimated)", estimatedFtp, [StringUtils formatActivityMeasureType:MEASURE_POWER]];
								else
									cell.detailTextLabel.text = [[NSString alloc] initWithFormat:@"Not Set"];
							}
						}
						break;
					default:
						break;
				}
			}
			break;
		case NUM_PROFILE_SECTIONS:
			break;
	}

	cell.selectionStyle = UITableViewCellSelectionStyleGray;
	return cell;
}

- (void)tableView:(UITableView*)tableView willDisplayCell:(UITableViewCell*)cell forRowAtIndexPath:(NSIndexPath*)indexPath
{
	NSInteger section = [indexPath section];

	switch (section)
	{
		case SECTION_USER:
			cell.accessoryType = UITableViewCellAccessoryNone;
			break;
		case SECTION_PERFORMANCE:
			cell.accessoryType = UITableViewCellAccessoryNone;
			break;
	}
}

- (void)tableView:(UITableView*)tableView didSelectRowAtIndexPath:(NSIndexPath*)indexPath
{
	NSInteger section = [indexPath section];

	if (section == SECTION_USER)
	{
		NSInteger row = [indexPath row];

		switch (row)
		{
			case ROW_GENDER:
				{
					AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
					UIAlertController* alertController = [UIAlertController alertControllerWithTitle:nil
																							 message:STR_GENDER
																					  preferredStyle:UIAlertControllerStyleAlert];
					[alertController addAction:[UIAlertAction actionWithTitle:[StringUtils genderToStr:GENDER_MALE] style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
						[appDelegate setUserGender:GENDER_MALE];
						[self.profileTableView reloadData];
					}]];
					[alertController addAction:[UIAlertAction actionWithTitle:[StringUtils genderToStr:GENDER_FEMALE] style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
						[appDelegate setUserGender:GENDER_FEMALE];
						[self.profileTableView reloadData];
					}]];
					[self presentViewController:alertController animated:YES completion:nil];
				}
				break;
			case ROW_BIRTHDATE:
				[self performSegueWithIdentifier:@SEGUE_TO_DATE_VIEW sender:self];
				break;
			case ROW_HEIGHT:
				{
					UIAlertController* alertController = [UIAlertController alertControllerWithTitle:STR_HEIGHT
																							 message:ALERT_MSG_HEIGHT
																					  preferredStyle:UIAlertControllerStyleAlert];

					[alertController addTextFieldWithConfigurationHandler:^(UITextField* textField) {
						AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
						textField.placeholder = [[NSString alloc] initWithFormat:@"%0.1f", [appDelegate userHeight]];
						textField.keyboardType = UIKeyboardTypeNumberPad;
					}];
					[alertController addAction:[UIAlertAction actionWithTitle:STR_OK style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
						UITextField* field = alertController.textFields.firstObject;
						double height = [[field text] doubleValue];

						if (height > (double)0.0)
						{
							AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
							[appDelegate setUserHeight:height];
							[self.profileTableView reloadData];
						}
					}]];
					[self presentViewController:alertController animated:YES completion:nil];
				}
				break;
			case ROW_WEIGHT:
				{
					AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
					UIAlertController* alertController = [UIAlertController alertControllerWithTitle:STR_WEIGHT
																							 message:ALERT_MSG_WEIGHT
																					  preferredStyle:UIAlertControllerStyleAlert];
					
					[alertController addTextFieldWithConfigurationHandler:^(UITextField* textField) {
						textField.placeholder = [[NSString alloc] initWithFormat:@"%0.1f", [appDelegate userWeight]];
						textField.keyboardType = UIKeyboardTypeNumberPad;
					}];
					[alertController addAction:[UIAlertAction actionWithTitle:STR_OK style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
						UITextField* field = alertController.textFields.firstObject;
						double weight = [[field text] doubleValue];

						if (weight > (double)0.0)
						{
							[appDelegate setUserWeight:weight];
							[self.profileTableView reloadData];
						}
					}]];
					[self presentViewController:alertController animated:YES completion:nil];
				}
				break;
			case NUM_PROFILE_USER_ROWS:
				break;
		}
		if (section == SECTION_PERFORMANCE)
		{
			NSInteger row = [indexPath row];

			switch (row)
			{
			case ROW_ACTIVITY_LEVEL:
				{
					AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
					UIAlertController* alertController = [UIAlertController alertControllerWithTitle:nil
																							 message:ACTION_SHEET_TITLE_ACTIVITY_LEVEL
																					  preferredStyle:UIAlertControllerStyleAlert];
					[alertController addAction:[UIAlertAction actionWithTitle:[StringUtils activityLevelToStr:ACTIVITY_LEVEL_SEDENTARY] style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
						[appDelegate setUserActivityLevel:ACTIVITY_LEVEL_SEDENTARY];
						[self.profileTableView reloadData];
					}]];
					[alertController addAction:[UIAlertAction actionWithTitle:[StringUtils activityLevelToStr:ACTIVITY_LEVEL_LIGHT] style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
						[appDelegate setUserActivityLevel:ACTIVITY_LEVEL_LIGHT];
						[self.profileTableView reloadData];
					}]];
					[alertController addAction:[UIAlertAction actionWithTitle:[StringUtils activityLevelToStr:ACTIVITY_LEVEL_MODERATE] style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
						[appDelegate setUserActivityLevel:ACTIVITY_LEVEL_MODERATE];
						[self.profileTableView reloadData];
					}]];
					[alertController addAction:[UIAlertAction actionWithTitle:[StringUtils activityLevelToStr:ACTIVITY_LEVEL_ACTIVE] style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
						[appDelegate setUserActivityLevel:ACTIVITY_LEVEL_ACTIVE];
						[self.profileTableView reloadData];
					}]];
					[alertController addAction:[UIAlertAction actionWithTitle:[StringUtils activityLevelToStr:ACTIVITY_LEVEL_EXTREME] style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
						[appDelegate setUserActivityLevel:ACTIVITY_LEVEL_EXTREME];
						[self.profileTableView reloadData];
					}]];
					[self presentViewController:alertController animated:YES completion:nil];
				}
				break;
			case ROW_FTP:
				{
					AppDelegate* appDelegate = (AppDelegate*)[[UIApplication sharedApplication] delegate];
					UIAlertController* alertController = [UIAlertController alertControllerWithTitle:STR_FTP
																							 message:ALERT_MSG_FTP
																					  preferredStyle:UIAlertControllerStyleAlert];
					
					[alertController addTextFieldWithConfigurationHandler:^(UITextField* textField) {
						textField.placeholder = [[NSString alloc] initWithFormat:@"%0.0f", [appDelegate userSpecifiedFtp]];
						textField.keyboardType = UIKeyboardTypeNumberPad;
					}];
					[alertController addAction:[UIAlertAction actionWithTitle:STR_OK style:UIAlertActionStyleDefault handler:^(UIAlertAction* action) {
						UITextField* field = alertController.textFields.firstObject;
						double ftp = [[field text] doubleValue];

						if (ftp > (double)0.0)
						{
							[appDelegate setUserFtp:ftp];
							[self.profileTableView reloadData];
						}
					}]];
					[self presentViewController:alertController animated:YES completion:nil];
				}
				break;
			case NUM_PROFILE_PERFORMANCE_ROWS:
				break;
			}
		}
	}
}

@end
