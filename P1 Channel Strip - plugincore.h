// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.h
//
/**
    \file   plugincore.h
    \author Will Pirkle
    \date   17-September-2018
    \brief  base class interface file for ASPiK plugincore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#ifndef __pluginCore_h__
#define __pluginCore_h__

#include "pluginbase.h"
#include "fxobjects.h"

// **--0x7F1F--**

// --- Plugin Variables controlID Enumeration 

enum controlID {
	boxgain = 0,
	sharpgain = 1,
	airgain = 2,
	boxfc = 10,
	boxq = 20,
	inlvl = 40,
	outlvl = 42,
	sharpfc = 11,
	sharpq = 21,
	airfc = 12,
	gatethresh = 4,
	gateattack = 24,
	gaterelease = 34,
	gategain = 44,
	compthresh = 5,
	compratio = 15,
	compattack = 25,
	comprelease = 35,
	compgain = 45,
	verbgain = 7,
	delayfb = 8,
	delaytime = 18,
	drygain = 17,
	verbtime = 27,
	preverbtime = 37,
	verbtime2 = 47,
	delaydry = 9,
	delaywet = 19,
	eqmute = 22,
	bpmdelay = 28,
	prein = 50,
	presat = 51,
	preass = 52,
	preout = 53,
	preampmute = 54
};

	// **--0x0F1F--**

/**
\class PluginCore
\ingroup ASPiK-Core
\brief
The PluginCore object is the default PluginBase derived object for ASPiK projects.
Note that you are fre to change the name of this object (as long as you change it in the compiler settings, etc...)


PluginCore Operations:
- overrides the main processing functions from the base class
- performs reset operation on sub-modules
- processes audio
- processes messages for custom views
- performs pre and post processing functions on parameters and audio (if needed)

\author Will Pirkle http://www.willpirkle.com
\remark This object is included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
class PluginCore : public PluginBase
{
public:
    PluginCore();

	/** Destructor: empty in default version */
    virtual ~PluginCore(){}

	// --- PluginBase Overrides ---
	//
	/** this is the creation function for all plugin parameters */
	bool initPluginParameters();

	/** called when plugin is loaded, a new audio file is playing or sample rate changes */
	virtual bool reset(ResetInfo& resetInfo);

	/** one-time post creation init function; pluginInfo contains path to this plugin */
	virtual bool initialize(PluginInfo& _pluginInfo);

	// --- preProcess: sync GUI parameters here; override if you don't want to use automatic variable-binding
	virtual bool preProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** process frames of data */
	virtual bool processAudioFrame(ProcessFrameInfo& processFrameInfo);

	// --- uncomment and override this for buffer processing; see base class implementation for
	//     help on breaking up buffers and getting info from processBufferInfo
	//virtual bool processAudioBuffers(ProcessBufferInfo& processBufferInfo);

	/** preProcess: do any post-buffer processing required; default operation is to send metering data to GUI  */
	virtual bool postProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo);

	/** this can be called: 1) after bound variable has been updated or 2) after smoothing occurs  */
	virtual bool postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** this is ony called when the user makes a GUI control change */
	virtual bool guiParameterChanged(int32_t controlID, double actualValue);

	/** processMessage: messaging system; currently used for custom/special GUI operations */
	virtual bool processMessage(MessageInfo& messageInfo);

	/** processMIDIEvent: MIDI event processing */
	virtual bool processMIDIEvent(midiEvent& event);

	/** specialized joystick servicing (currently not used) */
	virtual bool setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData);

	/** create the presets */
	bool initPluginPresets();

	// --- BEGIN USER VARIABLES AND FUNCTIONS -------------------------------------- //
	//	   Add your variables and methods here

	void UpdateParameters(double BPM);

	double gain_cooked_in = 1.0;
	double gain_cooked_out = 1.0;

	ClassATubePre preamp;

	AudioFilter HPass;
	AudioFilter Notch1;
	AudioFilter Notch2;
	AudioFilter HShelf;

	DynamicsProcessor Gate;
	DynamicsProcessor Comp;

	ReverbTank Verb;
	AudioDelay Delay;

	HostInfo infoBPM;

	// --- END USER VARIABLES AND FUNCTIONS -------------------------------------- //

private:
	//  **--0x07FD--**

	// --- Continuous Plugin Variables 
	double boxgain = 0.0;
	double sharpgain = 0.0;
	double airgain = 0.0;
	double boxfc = 0.0;
	double boxq = 0.0;
	double inlvl = 0.0;
	double outlvl = 0.0;
	double sharpfc = 0.0;
	double sharpq = 0.0;
	double airfc = 0.0;
	double gatethresh = 0.0;
	double gateattack = 0.0;
	double gaterelease = 0.0;
	double gategain = 0.0;
	double compthresh = 0.0;
	double compratio = 0.0;
	double compattack = 0.0;
	double comprelease = 0.0;
	double compgain = 0.0;
	double verbgain = 0.0;
	double delayfb = 0.0;
	double delaytime = 0.0;
	double drygain = 0.0;
	double verbtime = 0.0;
	double preverbtime = 0.0;
	double verbtime2 = 0.0;
	double delaydry = 0.0;
	double delaywet = 0.0;
	double prein = 0.0;
	double presat = 0.0;
	double preass = 0.0;
	double preout = 0.0;

	// --- Discrete Plugin Variables 
	int eqmute = 0;
	enum class eqmuteEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(eqmuteEnum::SWITCH_OFF, eqmute)) etc... 

	int bpmdelay = 0;
	enum class bpmdelayEnum { Quarter,Dotted4,Eighth,Dotted8 };	// to compare: if(compareEnumToInt(bpmdelayEnum::Quarter, bpmdelay)) etc... 

	int preampmute = 0;
	enum class preampmuteEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(preampmuteEnum::SWITCH_OFF, preampmute)) etc... 

	// **--0x1A7F--**
    // --- end member variables

public:
    /** static description: bundle folder name

	\return bundle folder name as a const char*
	*/
    static const char* getPluginBundleName();

    /** static description: name

	\return name as a const char*
	*/
    static const char* getPluginName();

	/** static description: short name

	\return short name as a const char*
	*/
	static const char* getShortPluginName();

	/** static description: vendor name

	\return vendor name as a const char*
	*/
	static const char* getVendorName();

	/** static description: URL

	\return URL as a const char*
	*/
	static const char* getVendorURL();

	/** static description: email

	\return email address as a const char*
	*/
	static const char* getVendorEmail();

	/** static description: Cocoa View Factory Name

	\return Cocoa View Factory Name as a const char*
	*/
	static const char* getAUCocoaViewFactoryName();

	/** static description: plugin type

	\return type (FX or Synth)
	*/
	static pluginType getPluginType();

	/** static description: VST3 GUID

	\return VST3 GUID as a const char*
	*/
	static const char* getVSTFUID();

	/** static description: 4-char code

	\return 4-char code as int
	*/
	static int32_t getFourCharCode();

	/** initalizer */
	bool initPluginDescriptors();
    
    /** Status Window Messages for hosts that can show it */
    void sendHostTextMessage(std::string messageString)
    {
        HostMessageInfo hostMessageInfo;
        hostMessageInfo.hostMessage = sendRAFXStatusWndText;
        hostMessageInfo.rafxStatusWndText.assign(messageString);
        if(pluginHostConnector)
            pluginHostConnector->sendHostMessage(hostMessageInfo);
    }

};




#endif /* defined(__pluginCore_h__) */
