//
//  MobileRandomifyAppDelegate.h
//  MobileRandomify
//
//  Created by Joachim Bengtsson on 2011-08-03.
//  Copyright 2011 Spotify AB. All rights reserved.
//

#import <UIKit/UIKit.h>

@class LoginVC;

@interface MobileRandomifyAppDelegate : NSObject <UIApplicationDelegate>
@property(nonatomic,retain) IBOutlet UIWindow *window;
@property(nonatomic,retain) IBOutlet UINavigationController *navigationController;
@property(nonatomic,retain) IBOutlet LoginVC *loginVC;

-(void)loginWithUsername:(NSString*)user password:(NSString*)pass;
@end
