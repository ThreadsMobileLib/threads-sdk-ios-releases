//
//  IntegrationsViewController.swift
//  ExampleSwift
//
//  Created by Vitaliy Kuzmenko on 07/08/2019.
//  Copyright © 2019 Threads. All rights reserved.
//

import UIKit
import Threads

enum Design: Int {
    case `default`, alternative
}

class IntegrationsViewController: UITableViewController, IntegrationsProtocol {

    @IBOutlet var segmentedControl: UISegmentedControl!
    
    var design: Design = .default
    
    override func viewDidLoad() {
        super.viewDidLoad()

        segmentedControl.selectedSegmentIndex = design.rawValue
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        let tb = tabBarController as? MainViewController
        tb?.updateUnreadMessagesCountBadgeValue()
    }
    
    func getAttributes() -> THRAttributes {
        switch design {
        case .default:
            return AttributesHelper.getDefaultAttributes()
        case .alternative:
            return AttributesHelper.getAltAttributes()
        }
    }
    
    func getChatViewController() -> UIViewController {
        let attributes = getAttributes()
        let chatViewController = Threads.threads().chatViewController(with: attributes)
        return chatViewController
    }

    // MARK: - Push Integrations
    
    /**
     In this method you can se how to implement simple Chat push to current navigation controller
     */
    func pushChatInCurrentNavigationController() {
        let chatViewController = getChatViewController()
        navigationController?.pushViewController(chatViewController, animated: true)
    }
    
    /**
     In this method you can se how to implement simple Chat push to current navigation controller with hiding tabBar.
     Like set Storyboard Parameter: (Hide Bottom Bar on Push) = YES
     */
    func pushChatInCurrentNavigationControllerWithHidingTabBar() {
        let chatViewController = getChatViewController()
        chatViewController.hidesBottomBarWhenPushed = true
        navigationController?.pushViewController(chatViewController, animated: true)
    }
    
    // MARK: - Present Integrations
    
    /**
     In this method you can see how to implement presenting Chat in UINavigationController as rootViewController
     */
    func presentChatInUINavigationController() {
        let chatViewController = getChatViewController()
        let nc = UINavigationController(rootViewController: chatViewController)
        nc.modalPresentationStyle = .fullScreen
        present(nc, animated: true, completion: nil)
    }
    
    /**
     In this method you can see how to implement presenting Chat as tab in UITabBarController from code
     */
    func presentChatUINavigationControllerAsTabInTabBarControllerInitializatedFromCode() {
        let chatViewController = getChatViewController()
        
        let nc = UINavigationController(rootViewController: chatViewController)
        nc.tabBarItem = UITabBarItem(title: NSLocalizedString("Chat", comment: ""), image: UIImage(named: "tabBarItemChat"), tag: 0)
        
        let tabBarController = UITabBarController()
        tabBarController.viewControllers = [nc]
        tabBarController.modalPresentationStyle = .fullScreen
        
        present(tabBarController, animated: true, completion: nil)
    }
    
    /**
     In this method you can see how to implement presenting Chat as tab in UITabBarController from storyboard
     See:
     - ChatInTabNavigationController
     - Main.storyboard ("Shared" Group)
     */
    func presentChatUINavigationControllerAsTabInTabBarControllerInitializatedFromStoryboard() {
        performSegue(withIdentifier: "ChatTabBarControllerSegueIdentifier", sender: nil)
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        
        if (segue.identifier == "ChatTabBarControllerSegueIdentifier") {
            let tabController = segue.destination as? UITabBarController
            let chatInTabVC = tabController?.viewControllers?[0] as? ChatInTabNavigationController
            chatInTabVC?.design = self.design;
        }
    }
    
    @objc func presentFromPush(withDesign design: Int) {
        if navigationController!.viewControllers.count > 1 || navigationController?.presentedViewController != nil { return }
        self.design = Design(rawValue: design)!
        let chatViewController = getChatViewController()
        navigationController?.viewControllers.append(chatViewController)
    }
    
    @IBAction func designDidChange() {
        self.design = Design(rawValue: segmentedControl.selectedSegmentIndex)!
    }

}
