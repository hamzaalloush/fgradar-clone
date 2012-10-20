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




