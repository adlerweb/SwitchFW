<?PHP

   require('eeprom.def.php');

    //General Coniguration
    $nodeid = 0x0100;       //Node ID
                            //This identifies your node. Its used to send
                            //configuration changes, query its status, etc
                            //every ID must be unique in your network!
                            //0x0000 to 0x0009 are reserved
                            //0x0010 to 0xFFFE allowed - this equals to 65524 nodes max

    $incfg = 0b11111111;    //1 = active, 0 = inactive - left digit equals to channel 7
    
    $outcfg[0]  =   array(  //Configuration for output channel 0
                        'active' => 1,      //1 = active, 0 = disabled
                        'invert' => 0,      //invert output
                        'pulse'  => 0,      //only pulse output regradless of received message
                                            //useful for stepping switch, door opener, etc
                        'boot'   => 0       //turn port on after reboot
                    );
    
    $outcfg[1]  =   array(  //Configuration for output channel 1
                        'active' => 1,      //1 = active, 0 = disabled
                        'invert' => 0,      //invert output
                        'pulse'  => 0,      //only pulse output regradless of received message
                                            //useful for stepping switch, door opener, etc
                        'boot'   => 0       //turn port on after reboot
                    );
    
    $outcfg[2]  =   array(  //Configuration for output channel 2
                        'active' => 1,      //1 = active, 0 = disabled
                        'invert' => 0,      //invert output
                        'pulse'  => 0,      //only pulse output regradless of received message
                                            //useful for stepping switch, door opener, etc
                        'boot'   => 0       //turn port on after reboot
                    );
    
    $outcfg[3]  =   array(  //Configuration for output channel 3
                        'active' => 0,      //1 = active, 0 = disabled
                        'invert' => 0,      //invert output
                        'pulse'  => 0,      //only pulse output regradless of received message
                                            //useful for stepping switch, door opener, etc
                        'boot'   => 0       //turn port on after reboot
                    );
    
    $outcfg[4]  =   array(  //Configuration for output channel 4
                        'active' => 0,      //1 = active, 0 = disabled
                        'invert' => 0,      //invert output
                        'pulse'  => 0,      //only pulse output regradless of received message
                                            //useful for stepping switch, door opener, etc
                        'boot'   => 0       //turn port on after reboot
                    );
    
    $outcfg[5]  =   array(  //Configuration for output channel 5
                        'active' => 0,      //1 = active, 0 = disabled
                        'invert' => 0,      //invert output
                        'pulse'  => 0,      //only pulse output regradless of received message
                                            //useful for stepping switch, door opener, etc
                        'boot'   => 0       //turn port on after reboot
                    );
    
    $outcfg[6]  =   array(  //Configuration for output channel 6
                        'active' => 1,      //1 = active, 0 = disabled
                        'invert' => 0,      //invert output
                        'pulse'  => 0,      //only pulse output regradless of received message
                                            //useful for stepping switch, door opener, etc
                        'boot'   => 0       //turn port on after reboot
                    );
    
    $outcfg[7]  =   array(  //Configuration for output channel 7
                        'active' => 1,      //1 = active, 0 = disabled
                        'invert' => 0,      //invert output
                        'pulse'  => 0,      //only pulse output regradless of received message
                                            //useful for stepping switch, door opener, etc
                        'boot'   => 0       //turn port on after reboot
                    );






    
    $groups[] = array(  //Sample input definition - example is for a standard switch toggeling light when pressed regradless of switch position
                    'address' => 0x1001,            //Group address
                    'io'      => INPUT,             //This defines an input
                    'channel' => 0,                 //Input channel 2
                    'trigger' => TRIGGER_BOTH,      //Trigger on falling and rising input
                    'msg'     => TURN_TOGGLE        //Toggle light when triggered
                );    

    $groups[] = array(  //Sample input definition - example is for a standard switch toggeling light when pressed regradless of switch position
                    'address' => 0x1001,            //Group address
                    'io'      => INPUT,             //This defines an input
                    'channel' => 1,                 //Input channel 2
                    'trigger' => TRIGGER_BOTH,      //Trigger on falling and rising input
                    'msg'     => TURN_TOGGLE        //Toggle light when triggered
                );    

    $groups[] = array(  //Sample input definition - example is for a standard switch toggeling light when pressed regradless of switch position
                    'address' => 0x1002,            //Group address
                    'io'      => INPUT,             //This defines an input
                    'channel' => 2,                 //Input channel 2
                    'trigger' => TRIGGER_BOTH,      //Trigger on falling and rising input
                    'msg'     => TURN_TOGGLE        //Toggle light when triggered
                );    

    $groups[] = array(  //Sample input definition - example is for a standard switch toggeling light when pressed regradless of switch position
                    'address' => 0x1003,            //Group address
                    'io'      => INPUT,             //This defines an input
                    'channel' => 3,                 //Input channel 2
                    'trigger' => TRIGGER_BOTH,      //Trigger on falling and rising input
                    'msg'     => TURN_TOGGLE        //Toggle light when triggered
                );    

    $groups[] = array(  //Sample input definition - example is for a standard switch toggeling light when pressed regradless of switch position
                    'address' => 0x1004,            //Group address
                    'io'      => INPUT,             //This defines an input
                    'channel' => 4,                 //Input channel 2
                    'trigger' => TRIGGER_BOTH,      //Trigger on falling and rising input
                    'msg'     => TURN_TOGGLE        //Toggle light when triggered
                );    

    $groups[] = array(  //Sample input definition - example is for a standard switch toggeling light when pressed regradless of switch position
                    'address' => 0x1005,            //Group address
                    'io'      => INPUT,             //This defines an input
                    'channel' => 5,                 //Input channel 2
                    'trigger' => TRIGGER_BOTH,      //Trigger on falling and rising input
                    'msg'     => TURN_TOGGLE        //Toggle light when triggered
                );    

    $groups[] = array(  //Sample input definition - example is for a standard switch toggeling light when pressed regradless of switch position
                    'address' => 0x1006,            //Group address
                    'io'      => INPUT,             //This defines an input
                    'channel' => 6,                 //Input channel 2
                    'trigger' => TRIGGER_BOTH,      //Trigger on falling and rising input
                    'msg'     => TURN_TOGGLE        //Toggle light when triggered
                );    

    $groups[] = array(  //Sample input definition - example is for a standard switch toggeling light when pressed regradless of switch position
                    'address' => 0x1007,            //Group address
                    'io'      => INPUT,             //This defines an input
                    'channel' => 7,                 //Input channel 2
                    'trigger' => TRIGGER_BOTH,      //Trigger on falling and rising input
                    'msg'     => TURN_TOGGLE        //Toggle light when triggered
                );







    $groups[] = array( //Sample output definition - this it the corresponding light
                    'address' => 0x1001,            //Group address - same as above so we honour its signals
                    'io'      => OUTPUT,            //This is an output
                    'channel' => 7,                 //output channel 0
                                                    //Trigger and message are not used for now
                );
    $groups[] = array( //Sample output definition - this it the corresponding light
                    'address' => 0x1002,            //Group address - same as above so we honour its signals
                    'io'      => OUTPUT,            //This is an output
                    'channel' => 0,                 //output channel 0
                                                    //Trigger and message are not used for now
                );
    $groups[] = array( //Sample output definition - this it the corresponding light
                    'address' => 0x1003,            //Group address - same as above so we honour its signals
                    'io'      => OUTPUT,            //This is an output
                    'channel' => 1,                 //output channel 0
                                                    //Trigger and message are not used for now
                );
    $groups[] = array( //Sample output definition - this it the corresponding light
                    'address' => 0x1004,            //Group address - same as above so we honour its signals
                    'io'      => OUTPUT,            //This is an output
                    'channel' => 2,                 //output channel 0
                                                    //Trigger and message are not used for now
                );
    $groups[] = array( //Sample output definition - this it the corresponding light
                    'address' => 0x1005,            //Group address - same as above so we honour its signals
                    'io'      => OUTPUT,            //This is an output
                    'channel' => 6,                 //output channel 0
                                                    //Trigger and message are not used for now
                );

   
   require('eeprom.inc.php');
?>
