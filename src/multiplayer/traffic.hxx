#ifndef __TRAFFIC_HXX
#define __TRAFFIC_HXX

 #include <simgear/structure/subsystem_mgr.hxx>
 #include "../flightgear/mpmessages.hxx"

 class FGMultiplayerTraffic : public SGSubsystem {
 public:
	FGMultiplayerTraffic();
	~FGMultiplayerTraffic();

	virtual void update(double);
 protected:
 private:
 };
#endif

