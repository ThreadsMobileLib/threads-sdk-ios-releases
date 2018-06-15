//
//  AboutViewController.m
//  ThreadsApp
//
//  Created by Brooma Service on 18/04/17.
//  Copyright © 2017 Brooma Service. All rights reserved.
//

#import "AboutViewController.h"

@interface AboutViewController ()

@end

@implementation AboutViewController

#pragma mark - Life Cycle

- (void)viewDidLoad {
    [super viewDidLoad];
    self.navigationItem.title = NSLocalizedString(@"unreaded_messages_test", nil);
    self.titleLabel.text = NSLocalizedString(@"unreaded_messages", nil);
    [self updateCouterLabel];
}

- (void)setCounterValue:(NSInteger)counterValue {
    _counterValue = counterValue;
    [self updateCouterLabel];

}

- (void) updateCouterLabel {
    if (self.counterLabel) {
        self.counterLabel.text = [NSString stringWithFormat: @"%ld", self.counterValue];
    }
}

@end
