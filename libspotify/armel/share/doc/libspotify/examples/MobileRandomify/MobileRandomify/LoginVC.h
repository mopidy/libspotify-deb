//
//  RootViewController.h
//  MobileRandomify
//
//  Created by Joachim Bengtsson on 2011-08-03.
//  Copyright 2011 Spotify AB. All rights reserved.
//

#import <UIKit/UIKit.h>

@class MobileRandomifyAppDelegate;

@interface LoginVC : UIViewController <UITextFieldDelegate>
@property(nonatomic,retain) IBOutlet UITextField *username;
@property(nonatomic,retain) IBOutlet UITextField *password;
@property(nonatomic,assign) MobileRandomifyAppDelegate *appDelegate;
@end
