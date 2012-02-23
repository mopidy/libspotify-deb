//
//  RootViewController.m
//  MobileRandomify
//
//  Created by Joachim Bengtsson on 2011-08-03.
//  Copyright 2011 Spotify AB. All rights reserved.
//

#import "LoginVC.h"
#import "MobileRandomifyAppDelegate.h"

@interface LoginVC ()
-(void)login;
@end

@implementation LoginVC
@synthesize username = _username, password = _password, appDelegate = _appDelegate;
- (void)dealloc
{
	self.username = self.password = (id)nil;
    [super dealloc];
}
-(void)viewDidLoad;
{
	[super viewDidLoad];
	self.title = @"Log in";
}

-(void)viewWillAppear:(BOOL)animated;
{
	[super viewWillAppear:animated];
	self.username.enabled = self.password.enabled = YES;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField;
{
	if(textField == _username)
		[_password becomeFirstResponder];
	else
		[self login];
	return NO;
}

-(void)login;
{
	[_appDelegate loginWithUsername:self.username.text password:self.password.text];
	self.username.enabled = self.password.enabled = NO;
}
@end
