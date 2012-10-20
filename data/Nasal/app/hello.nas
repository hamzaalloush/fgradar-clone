var path = "/foo/bar/value";
var value = 1000;

setprop(path, value);
if (getprop(path) != value) 
 die("setprop/getprop not working properly!");
else
 print("Success: setprop/getprop support works!");


var listener_test = "/test/listener/value";
setlistener(listener_test, func print("SUCCESS: listeners work"));

settimer( func setprop(listener_test,100), 5.00);

var ping = func print("Ping from Nasal callback via timer") and settimer(ping,1);

var start=systime();
print("Hello FGRadar from a Nasal script :) ");

for (var i=0;i<10000;i+=1) {
 nil;
}

print("Delay:", systime() - start);
ping();
