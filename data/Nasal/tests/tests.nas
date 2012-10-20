###
# This file contains a bunch of self tests (aka "unit tests") to ensure that our commits
# don't break any existing features
#

var path = "/foo/bar/value";
var value = 1000;

setprop(path, value);
if (getprop(path) != value) 
 die("setprop/getprop not working properly!");
else
 print("SUCCESS: setprop/getprop support works!");

var listeners_work = 0;
var listener_test = "/test/listener/value";
setlistener(listener_test, func {
	print("SUCCESS: listeners work"); 
	listeners_work=1;
	} 
);

setprop(listener_test, 1);
if (!listeners_work) die("Listeners are broken now!");


var timers_work = 0;
var timer_test = "/test/systime";
settimer( func print("SUCCESS: settimer() works") and timers_work=100, 0);
print("timer value is:", timers_work);
settimer(func print("Hello"), 0.1);
if (timer_test != 100) die ("Nasal timers are broken now!");


