// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.cpp
//
/**
    \file   plugincore.cpp
    \author Will Pirkle
    \date   17-September-2018
    \brief  Implementation file for PluginCore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#include "plugincore.h"
#include "plugindescription.h"

/**
\brief PluginCore constructor is launching pad for object initialization

Operations:
- initialize the plugin description (strings, codes, numbers, see initPluginDescriptors())
- setup the plugin's audio I/O channel support
- create the PluginParameter objects that represent the plugin parameters (see FX book if needed)
- create the presets
*/
PluginCore::PluginCore()
{
    // --- describe the plugin; call the helper to init the static parts you setup in plugindescription.h
    initPluginDescriptors();

    // --- default I/O combinations
	// --- for FX plugins
	if (getPluginType() == kFXPlugin)
	{
		addSupportedIOCombination({ kCFMono, kCFMono });
		addSupportedIOCombination({ kCFMono, kCFStereo });
		addSupportedIOCombination({ kCFStereo, kCFStereo });
	}
	else // --- synth plugins have no input, only output
	{
		addSupportedIOCombination({ kCFNone, kCFMono });
		addSupportedIOCombination({ kCFNone, kCFStereo });
	}

	// --- for sidechaining, we support mono and stereo inputs; auxOutputs reserved for future use
	addSupportedAuxIOCombination({ kCFMono, kCFNone });
	addSupportedAuxIOCombination({ kCFStereo, kCFNone });

	// --- create the parameters
    initPluginParameters();

    // --- create the presets
    initPluginPresets();
}

/**
\brief create all of your plugin parameters here

\return true if parameters were created, false if they already existed
*/
bool PluginCore::initPluginParameters()
{
	if (pluginParameterMap.size() > 0)
		return false;

    // --- Add your plugin parameter instantiation code bewtween these hex codes
	// **--0xDEA7--**


	// --- Declaration of Plugin Parameter Objects 
	PluginParameter* piParam = nullptr;

	// --- continuous control: Box Gain
	piParam = new PluginParameter(controlID::boxgain, "Box Gain", "", controlVariableType::kDouble, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boxgain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Sharp Gain
	piParam = new PluginParameter(controlID::sharpgain, "Sharp Gain", "", controlVariableType::kDouble, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&sharpgain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Air Gain
	piParam = new PluginParameter(controlID::airgain, "Air Gain", "", controlVariableType::kDouble, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&airgain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Box Freq
	piParam = new PluginParameter(controlID::boxfc, "Box Freq", "Hz", controlVariableType::kDouble, 300.000000, 650.000000, 450.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boxfc, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Box Q
	piParam = new PluginParameter(controlID::boxq, "Box Q", "", controlVariableType::kDouble, 0.000000, 12.000000, 6.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&boxq, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Input Gain
	piParam = new PluginParameter(controlID::inlvl, "Input Gain", "dB", controlVariableType::kDouble, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&inlvl, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Output Gain
	piParam = new PluginParameter(controlID::outlvl, "Output Gain", "dB", controlVariableType::kDouble, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&outlvl, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Sharp Freq
	piParam = new PluginParameter(controlID::sharpfc, "Sharp Freq", "Hz", controlVariableType::kDouble, 1000.000000, 4000.000000, 2500.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&sharpfc, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Sharp Q
	piParam = new PluginParameter(controlID::sharpq, "Sharp Q", "", controlVariableType::kDouble, 0.000000, 12.000000, 6.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&sharpq, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Air Freq
	piParam = new PluginParameter(controlID::airfc, "Air Freq", "Hz", controlVariableType::kDouble, 10000.000000, 20000.000000, 15000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&airfc, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Gate Threshold
	piParam = new PluginParameter(controlID::gatethresh, "Gate Threshold", "dB", controlVariableType::kDouble, -60.000000, 0.000000, -60.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&gatethresh, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Gate Attack
	piParam = new PluginParameter(controlID::gateattack, "Gate Attack", "mSec", controlVariableType::kDouble, 300.000000, 1000.000000, 300.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&gateattack, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Gate Release
	piParam = new PluginParameter(controlID::gaterelease, "Gate Release", "mSec", controlVariableType::kDouble, 300.000000, 1000.000000, 300.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&gaterelease, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Gate Out Gain
	piParam = new PluginParameter(controlID::gategain, "Gate Out Gain", "dB", controlVariableType::kDouble, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&gategain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Comp Threshold
	piParam = new PluginParameter(controlID::compthresh, "Comp Threshold", "dB", controlVariableType::kDouble, -36.000000, 0.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&compthresh, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Comp Ratio
	piParam = new PluginParameter(controlID::compratio, "Comp Ratio", "%", controlVariableType::kDouble, 1.000000, 100.000000, 50.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&compratio, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Comp Attack
	piParam = new PluginParameter(controlID::compattack, "Comp Attack", "mSec", controlVariableType::kDouble, 300.000000, 1000.000000, 300.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&compattack, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Comp Release
	piParam = new PluginParameter(controlID::comprelease, "Comp Release", "mSec", controlVariableType::kDouble, 300.000000, 1000.000000, 300.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&comprelease, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Comp Out Gain
	piParam = new PluginParameter(controlID::compgain, "Comp Out Gain", "dB", controlVariableType::kDouble, -12.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&compgain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Verb Wet
	piParam = new PluginParameter(controlID::verbgain, "Verb Wet", "dB", controlVariableType::kDouble, -60.000000, 0.000000, -60.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&verbgain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Delay Feedback
	piParam = new PluginParameter(controlID::delayfb, "Delay Feedback", "%", controlVariableType::kDouble, 0.000000, 100.000000, 20.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&delayfb, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Delay Time
	piParam = new PluginParameter(controlID::delaytime, "Delay Time", "mSec", controlVariableType::kDouble, 0.000000, 500.000000, 50.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&delaytime, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Verb Dry
	piParam = new PluginParameter(controlID::drygain, "Verb Dry", "dB", controlVariableType::kDouble, -60.000000, 0.000000, -60.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&drygain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Verb Time
	piParam = new PluginParameter(controlID::verbtime, "Verb Time", "mSec", controlVariableType::kDouble, 0.000000, 5000.000000, 10.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&verbtime, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Predelay
	piParam = new PluginParameter(controlID::preverbtime, "Predelay", "mSec", controlVariableType::kDouble, 0.000000, 500.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&preverbtime, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Reverb Time
	piParam = new PluginParameter(controlID::verbtime2, "Reverb Time", "", controlVariableType::kDouble, 0.000000, 1.000000, 0.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&verbtime2, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Delay Dry
	piParam = new PluginParameter(controlID::delaydry, "Delay Dry", "dB", controlVariableType::kDouble, -60.000000, 0.000000, -60.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&delaydry, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Delay Wet
	piParam = new PluginParameter(controlID::delaywet, "Delay Wet", "dB", controlVariableType::kDouble, -60.000000, 0.000000, -60.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&delaywet, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: VOCAL MUTE
	piParam = new PluginParameter(controlID::eqmute, "VOCAL MUTE", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&eqmute, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: BPM Delay
	piParam = new PluginParameter(controlID::bpmdelay, "BPM Delay", "Quarter,Dotted4,Eighth,Dotted8", "Quarter");
	piParam->setBoundVariable(&bpmdelay, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Input
	piParam = new PluginParameter(controlID::prein, "Input", "dB", controlVariableType::kDouble, -60.000000, 12.000000, -3.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&prein, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Saturation
	piParam = new PluginParameter(controlID::presat, "Saturation", "", controlVariableType::kDouble, 1.000000, 3.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&presat, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Assymetry
	piParam = new PluginParameter(controlID::preass, "Assymetry", "", controlVariableType::kDouble, 0.000000, 10.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&preass, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Output
	piParam = new PluginParameter(controlID::preout, "Output", "dB", controlVariableType::kDouble, -30.000000, 6.000000, -3.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&preout, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: PRE MUTE
	piParam = new PluginParameter(controlID::preampmute, "PRE MUTE", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&preampmute, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- Aux Attributes
	AuxParameterAttribute auxAttribute;

	// --- RAFX GUI attributes
	// --- controlID::boxgain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boxgain, auxAttribute);

	// --- controlID::sharpgain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::sharpgain, auxAttribute);

	// --- controlID::airgain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::airgain, auxAttribute);

	// --- controlID::boxfc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boxfc, auxAttribute);

	// --- controlID::boxq
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::boxq, auxAttribute);

	// --- controlID::inlvl
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::inlvl, auxAttribute);

	// --- controlID::outlvl
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::outlvl, auxAttribute);

	// --- controlID::sharpfc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::sharpfc, auxAttribute);

	// --- controlID::sharpq
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::sharpq, auxAttribute);

	// --- controlID::airfc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::airfc, auxAttribute);

	// --- controlID::gatethresh
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::gatethresh, auxAttribute);

	// --- controlID::gateattack
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::gateattack, auxAttribute);

	// --- controlID::gaterelease
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::gaterelease, auxAttribute);

	// --- controlID::gategain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::gategain, auxAttribute);

	// --- controlID::compthresh
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::compthresh, auxAttribute);

	// --- controlID::compratio
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::compratio, auxAttribute);

	// --- controlID::compattack
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::compattack, auxAttribute);

	// --- controlID::comprelease
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::comprelease, auxAttribute);

	// --- controlID::compgain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::compgain, auxAttribute);

	// --- controlID::verbgain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::verbgain, auxAttribute);

	// --- controlID::delayfb
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::delayfb, auxAttribute);

	// --- controlID::delaytime
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::delaytime, auxAttribute);

	// --- controlID::drygain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::drygain, auxAttribute);

	// --- controlID::verbtime
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::verbtime, auxAttribute);

	// --- controlID::preverbtime
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::preverbtime, auxAttribute);

	// --- controlID::verbtime2
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::verbtime2, auxAttribute);

	// --- controlID::delaydry
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::delaydry, auxAttribute);

	// --- controlID::delaywet
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::delaywet, auxAttribute);

	// --- controlID::eqmute
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741825);
	setParamAuxAttribute(controlID::eqmute, auxAttribute);

	// --- controlID::bpmdelay
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::bpmdelay, auxAttribute);

	// --- controlID::prein
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::prein, auxAttribute);

	// --- controlID::presat
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::presat, auxAttribute);

	// --- controlID::preass
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::preass, auxAttribute);

	// --- controlID::preout
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::preout, auxAttribute);

	// --- controlID::preampmute
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741825);
	setParamAuxAttribute(controlID::preampmute, auxAttribute);


	// **--0xEDA5--**
   
    // --- BONUS Parameter
    // --- SCALE_GUI_SIZE
    PluginParameter* piParamBonus = new PluginParameter(SCALE_GUI_SIZE, "Scale GUI", "tiny,small,medium,normal,large,giant", "normal");
    addPluginParameter(piParamBonus);

	// --- create the super fast access array
	initPluginParameterArray();

    return true;
}

/**
\brief initialize object for a new run of audio; called just before audio streams

Operation:
- store sample rate and bit depth on audioProcDescriptor - this information is globally available to all core functions
- reset your member objects here

\param resetInfo structure of information about current audio format

\return true if operation succeeds, false otherwise
*/
bool PluginCore::reset(ResetInfo& resetInfo)
{
    // --- save for audio processing
    audioProcDescriptor.sampleRate = resetInfo.sampleRate;
    audioProcDescriptor.bitDepth = resetInfo.bitDepth;

	 

	ClassATubePreParameters preparams = preamp.getParameters();
	preparams.highShelf_fc = 15000;
	preparams.highShelfBoostCut_dB = 2.5;
	preamp.setParameters(preparams);

	AudioFilterParameters hpassparams = HPass.getParameters();		// High Pass Filter at 200 Hz
	hpassparams.algorithm = filterAlgorithm::kHPF1;
	hpassparams.fc = 200;
	HPass.setParameters(hpassparams);
	HPass.reset(resetInfo.sampleRate);

	AudioFilterParameters notch1params = Notch1.getParameters();	// Parametric EQ 1
	notch1params.algorithm = filterAlgorithm::kCQParaEQ;
	Notch1.setParameters(notch1params);
	Notch1.reset(resetInfo.sampleRate);

	AudioFilterParameters notch2params = Notch2.getParameters();	// Parametric EQ 2
	notch2params.algorithm = filterAlgorithm::kCQParaEQ;
	Notch2.setParameters(notch2params);
	Notch2.reset(resetInfo.sampleRate);

	AudioFilterParameters hshelfparams = HShelf.getParameters();	// High Shelf Filter
	hshelfparams.algorithm = filterAlgorithm::kHiShelf;
	HShelf.setParameters(hshelfparams);
	HShelf.reset(resetInfo.sampleRate);

	DynamicsProcessorParameters gateparams = Gate.getParameters();	// Gate (Downward Expander)
	gateparams.calculation = dynamicsProcessorType::kDownwardExpander;
	gateparams.hardLimitGate = true;								// makes the ratio to infinity
	Gate.setParameters(gateparams);
	Gate.reset(resetInfo.sampleRate);

	DynamicsProcessorParameters compparams = Comp.getParameters();	// Compressor
	compparams.calculation = dynamicsProcessorType::kCompressor;
	Comp.setParameters(compparams);
	Comp.reset(resetInfo.sampleRate);

	ReverbTankParameters verbparams = Verb.getParameters();			// Reverb
	verbparams.density = reverbDensity::kThick;						// Thick Density
	Verb.setParameters(verbparams);
	Verb.reset(resetInfo.sampleRate);

	AudioDelayParameters delayparams = Delay.getParameters();		// Delay
	delayparams.algorithm = delayAlgorithm::kPingPong;
	delayparams.updateType = delayUpdateType::kLeftAndRight;
	Delay.setParameters(delayparams);
	Delay.reset(resetInfo.sampleRate);

	Delay.createDelayBuffers(resetInfo.sampleRate, 2000.0);

    // --- other reset inits
    return PluginBase::reset(resetInfo);
}

/**
\brief one-time initialize function called after object creation and before the first reset( ) call

Operation:
- saves structure for the plugin to use; you can also load WAV files or state information here
*/
bool PluginCore::initialize(PluginInfo& pluginInfo)
{
	// --- add one-time init stuff here

	return true;
}

/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- syncInBoundVariables when preProcessAudioBuffers is called, it is *guaranteed* that all GUI control change information
  has been applied to plugin parameters; this binds parameter changes to your underlying variables
- NOTE: postUpdatePluginParameter( ) will be called for all bound variables that are acutally updated; if you need to process
  them individually, do so in that function
- use this function to bulk-transfer the bound variable data into your plugin's member object variables

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::preProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
    // --- sync internal variables to GUI parameters; you can also do this manually if you don't
    //     want to use the auto-variable-binding
    syncInBoundVariables();

    return true;
}

/**
\brief frame-processing method

Operation:
- decode the plugin type - for synth plugins, fill in the rendering code; for FX plugins, delete the if(synth) portion and add your processing code
- note that MIDI events are fired for each sample interval so that MIDI is tightly sunk with audio
- doSampleAccurateParameterUpdates will perform per-sample interval smoothing

\param processFrameInfo structure of information about *frame* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processAudioFrame(ProcessFrameInfo& processFrameInfo)
{
	// --- fire any MIDI events for this sample interval
	processFrameInfo.midiEventQueue->fireMidiEvents(processFrameInfo.currentFrame);

	// --- do per-frame updates; VST automation and parameter smoothing
 	doSampleAccurateParameterUpdates();
 	double BPM = processFrameInfo.hostInfo->dBPM;
	UpdateParameters(BPM);

	double xnL = processFrameInfo.audioInputFrame[0];
	double xnR = processFrameInfo.audioInputFrame[1];

	double firstgainL = xnL * gain_cooked_in;
	double firstgainR = xnR * gain_cooked_in;

	double preampL, preampR;


	if (preampmute == 0)
	{
		preampL = preamp.processAudioSample(firstgainL);
		preampR = preamp.processAudioSample(firstgainR);
	}
	if (preampmute == 1)
	{
		preampL = firstgainL;
		preampR = firstgainR;
	}


	double gatedsigL = Gate.processAudioSample(preampL);
	double gatedsigR = Gate.processAudioSample(preampR);

	double compedsigL = Comp.processAudioSample(gatedsigL);
	double compedsigR = Comp.processAudioSample(gatedsigR);

	double highpassedsigL = HPass.processAudioSample(compedsigL);
	double highpassedsigR = HPass.processAudioSample(compedsigR);

	double notch1sigL = Notch1.processAudioSample(highpassedsigL);
	double notch1sigR = Notch1.processAudioSample(highpassedsigR);

	double notch2sigL = Notch2.processAudioSample(notch1sigL);
	double notch2sigR = Notch2.processAudioSample(notch1sigR);

	double hshelfsigL = HShelf.processAudioSample(notch2sigL);
	double hshelfsigR = HShelf.processAudioSample(notch2sigR);

	float inputFrame[2];

	if (eqmute == 0)		// if EQ MUTE is OFF
	{
		inputFrame[0] = hshelfsigL;
		inputFrame[1] = hshelfsigR;
	}
	if (eqmute == 1)		// if EQ MUTE is ON
	{
		inputFrame[0] = compedsigL;
		inputFrame[1] = compedsigR;
	}


	float ReverbFrame[2];
	float DelayFrame[2];

	Verb.processAudioFrame(inputFrame, ReverbFrame , processFrameInfo.numAudioInChannels, processFrameInfo.numAudioOutChannels);
	Delay.processAudioFrame(inputFrame, DelayFrame, processFrameInfo.numAudioInChannels, processFrameInfo.numAudioOutChannels);
	//Verb.processAudioFrame(processFrameInfo.audioInputFrame, processFrameInfo.audioOutputFrame, processFrameInfo.numAudioInChannels, processFrameInfo.numAudioOutChannels);
	double verbsigL = Verb.processAudioSample(hshelfsigL);
	double delaysigL = Delay.processAudioSample(hshelfsigL);

	double sumL = ((.6 * inputFrame[0]) + (.6 * DelayFrame[0]) + (.6 * ReverbFrame[0])) * gain_cooked_out;
	double sumR = ((.6 * inputFrame[1]) + (.6 * DelayFrame[1]) + (.6 * ReverbFrame[1])) * gain_cooked_out;

	//double delaysigL = Delay.processAudioSample(hshelfsigL);
	//double delaysigR = Delay.processAudioSample(hshelfsigR);


	double ynL = sumL;
	double ynR = sumR;

    // --- FX Plugin:
    if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFMono)
    {
		// --- pass through code: change this with your signal processing
		processFrameInfo.audioOutputFrame[0] = ynL; //processFrameInfo.audioInputFrame[0];

        return true; /// processed
    }

    // --- Mono-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
		processFrameInfo.audioOutputFrame[0] = ynL; //processFrameInfo.audioInputFrame[0];
		processFrameInfo.audioOutputFrame[1] = ynR; //processFrameInfo.audioInputFrame[0];

        return true; /// processed
    }

    // --- Stereo-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFStereo &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
		processFrameInfo.audioOutputFrame[0] = ynL; // processFrameInfo.audioInputFrame[0];
		processFrameInfo.audioOutputFrame[1] = ynR; // processFrameInfo.audioInputFrame[1];

        return true; /// processed
    }

    return false; /// NOT processed
}

void PluginCore::UpdateParameters(double BPM)
{
	gain_cooked_in = pow(10.0, inlvl / 20.0);
	gain_cooked_out = pow(10.0, outlvl / 20.0);

	ClassATubePreParameters preparams = preamp.getParameters();
	preparams.inputLevel_dB = prein;
	preparams.saturation = presat;
	preparams.asymmetry = preass;
	preparams.outputLevel_dB = preout;
	preamp.setParameters(preparams);

	AudioFilterParameters hpassparams = HPass.getParameters();			// High Pass EQ
	HPass.setParameters(hpassparams);

	AudioFilterParameters notch1params = Notch1.getParameters();		// Parametric EQ 1
	notch1params.boostCut_dB = boxgain;
	notch1params.fc = boxfc;
	notch1params.Q = boxq;
	Notch1.setParameters(notch1params);

	AudioFilterParameters notch2params = Notch2.getParameters();		// Parametric EQ 2
	notch2params.boostCut_dB = sharpgain;
	notch2params.fc = sharpfc;
	notch2params.Q = sharpq;
	Notch2.setParameters(notch2params);

	AudioFilterParameters hshelfparams = HShelf.getParameters();		// High Shelf EQ
	hshelfparams.boostCut_dB = airgain;
	hshelfparams.fc = airfc;
	HShelf.setParameters(hshelfparams);

	DynamicsProcessorParameters gateparams = Gate.getParameters();		// Gate
	gateparams.threshold_dB = gatethresh;
	// gateparams.gainReduction = gategainreduction;
	gateparams.attackTime_mSec = gateattack;
	gateparams.releaseTime_mSec = gaterelease;
	gateparams.outputGain_dB = gategain;
	Gate.setParameters(gateparams);

	DynamicsProcessorParameters compparams = Comp.getParameters();		// Compressor
	compparams.threshold_dB = compthresh;
	compparams.ratio = compratio;
	compparams.attackTime_mSec = compattack;
	compparams.releaseTime_mSec = comprelease;
	compparams.outputGain_dB = compgain;
	Comp.setParameters(compparams);

	ReverbTankParameters verbparams = Verb.getParameters();				// Reverb
	verbparams.fixeDelayMax_mSec = verbtime;
	verbparams.preDelayTime_mSec = preverbtime;
	verbparams.dryLevel_dB = drygain;
	verbparams.wetLevel_dB = verbgain;
	verbparams.kRT = verbtime2;
	Verb.setParameters(verbparams);


	//double BPM = infoBPM.dBPM;
	double Tquarter = BPM * 60000; 
	double Tqtrip = (Tquarter * 1.5);
	double Teighth = Tquarter / 2; 
	double Tetrip = (Teighth * 1.5);

	AudioDelayParameters delayparams = Delay.getParameters();			// Delay
	delayparams.feedback_Pct = delayfb;

	
	if (bpmdelay == 0)
	{
		delayparams.leftDelay_mSec = Tquarter;
		delayparams.rightDelay_mSec = Tquarter;
	}
	if (bpmdelay == 1)
	{
		delayparams.leftDelay_mSec = Tqtrip;
		delayparams.rightDelay_mSec = Tqtrip;
	}
	if (bpmdelay == 2)
	{
		delayparams.leftDelay_mSec = Teighth;
		delayparams.rightDelay_mSec = Teighth;
	}
	if (bpmdelay == 3)
	{
		delayparams.leftDelay_mSec = Tetrip;
		delayparams.rightDelay_mSec = Tetrip;
	}
	
	
	//delayparams.leftDelay_mSec = delaytime;
	//delayparams.rightDelay_mSec = delaytime;

	delayparams.dryLevel_dB = delaydry;
	delayparams.wetLevel_dB = delaywet;
	Delay.setParameters(delayparams);

}

/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- updateOutBoundVariables sends metering data to the GUI meters

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
	// --- update outbound variables; currently this is meter data only, but could be extended
	//     in the future
	updateOutBoundVariables();

    return true;
}

/**
\brief update the PluginParameter's value based on GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- use base class helper
    setPIParamValue(controlID, controlValue);

    // --- do any post-processing
    postUpdatePluginParameter(controlID, controlValue, paramInfo);

    return true; /// handled
}

/**
\brief update the PluginParameter's value based on *normlaized* GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param normalizedValue the new control value in normalized form
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo)
{
	// --- use base class helper, returns actual value
	double controlValue = setPIParamValueNormalized(controlID, normalizedValue, paramInfo.applyTaper);

	// --- do any post-processing
	postUpdatePluginParameter(controlID, controlValue, paramInfo);

	return true; /// handled
}

/**
\brief perform any operations after the plugin parameter has been updated; this is one paradigm for
	   transferring control information into vital plugin variables or member objects. If you use this
	   method you can decode the control ID and then do any cooking that is needed. NOTE: do not
	   overwrite bound variables here - this is ONLY for any extra cooking that is required to convert
	   the GUI data to meaninful coefficients or other specific modifiers.

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- now do any post update cooking; be careful with VST Sample Accurate automation
    //     If enabled, then make sure the cooking functions are short and efficient otherwise disable it
    //     for the Parameter involved
    /*switch(controlID)
    {
        case 0:
        {
            return true;    /// handled
        }

        default:
            return false;   /// not handled
    }*/

    return false;
}

/**
\brief has nothing to do with actual variable or updated variable (binding)

CAUTION:
- DO NOT update underlying variables here - this is only for sending GUI updates or letting you
  know that a parameter was changed; it should not change the state of your plugin.

WARNING:
- THIS IS NOT THE PREFERRED WAY TO LINK OR COMBINE CONTROLS TOGETHER. THE PROPER METHOD IS
  TO USE A CUSTOM SUB-CONTROLLER THAT IS PART OF THE GUI OBJECT AND CODE.
  SEE http://www.willpirkle.com for more information

\param controlID the control ID value of the parameter being updated
\param actualValue the new control value

\return true if operation succeeds, false otherwise
*/
bool PluginCore::guiParameterChanged(int32_t controlID, double actualValue)
{
	/*
	switch (controlID)
	{
		case controlID::<your control here>
		{

			return true; // handled
		}

		default:
			break;
	}*/

	return false; /// not handled
}

/**
\brief For Custom View and Custom Sub-Controller Operations

NOTES:
- this is for advanced users only to implement custom view and custom sub-controllers
- see the SDK for examples of use

\param messageInfo a structure containing information about the incoming message

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMessage(MessageInfo& messageInfo)
{
	// --- decode message
	switch (messageInfo.message)
	{
		// --- add customization appearance here
	case PLUGINGUI_DIDOPEN:
	{
		return false;
	}

	// --- NULL pointers so that we don't accidentally use them
	case PLUGINGUI_WILLCLOSE:
	{
		return false;
	}

	// --- update view; this will only be called if the GUI is actually open
	case PLUGINGUI_TIMERPING:
	{
		return false;
	}

	// --- register the custom view, grab the ICustomView interface
	case PLUGINGUI_REGISTER_CUSTOMVIEW:
	{

		return false;
	}

	case PLUGINGUI_REGISTER_SUBCONTROLLER:
	case PLUGINGUI_QUERY_HASUSERCUSTOM:
	case PLUGINGUI_USER_CUSTOMOPEN:
	case PLUGINGUI_USER_CUSTOMCLOSE:
	case PLUGINGUI_EXTERNAL_SET_NORMVALUE:
	case PLUGINGUI_EXTERNAL_SET_ACTUALVALUE:
	{

		return false;
	}

	default:
		break;
	}

	return false; /// not handled
}


/**
\brief process a MIDI event

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param event a structure containing the MIDI event data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMIDIEvent(midiEvent& event)
{
	return true;
}

/**
\brief (for future use)

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param vectorJoysickData a structure containing joystick data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData)
{
	return true;
}

/**
\brief use this method to add new presets to the list

NOTES:
- see the SDK for examples of use
- for non RackAFX users that have large paramter counts, there is a secret GUI control you
  can enable to write C++ code into text files, one per preset. See the SDK or http://www.willpirkle.com for details

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginPresets()
{
	// **--0xFF7A--**

	// --- Plugin Presets 
	int index = 0;
	PresetInfo* preset = nullptr;

	// --- Preset: Factory Preset
	preset = new PresetInfo(index++, "Factory Preset");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::boxgain, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::sharpgain, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::airgain, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::boxfc, 450.000000);
	setPresetParameter(preset->presetParameters, controlID::boxq, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::inlvl, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::outlvl, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::sharpfc, 2500.000000);
	setPresetParameter(preset->presetParameters, controlID::sharpq, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::airfc, 15000.000000);
	setPresetParameter(preset->presetParameters, controlID::gatethresh, -60.000000);
	setPresetParameter(preset->presetParameters, controlID::gateattack, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::gaterelease, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::gategain, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::compthresh, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::compratio, 50.000000);
	setPresetParameter(preset->presetParameters, controlID::compattack, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::comprelease, 300.000000);
	setPresetParameter(preset->presetParameters, controlID::compgain, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::verbgain, -60.000000);
	setPresetParameter(preset->presetParameters, controlID::delayfb, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::delaytime, 50.000000);
	setPresetParameter(preset->presetParameters, controlID::drygain, -60.000000);
	setPresetParameter(preset->presetParameters, controlID::verbtime, 10.000000);
	setPresetParameter(preset->presetParameters, controlID::preverbtime, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::verbtime2, 0.500000);
	setPresetParameter(preset->presetParameters, controlID::delaydry, -60.000000);
	setPresetParameter(preset->presetParameters, controlID::delaywet, -60.000000);
	setPresetParameter(preset->presetParameters, controlID::eqmute, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::bpmdelay, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::prein, -3.000000);
	setPresetParameter(preset->presetParameters, controlID::presat, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::preass, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::preout, -3.000000);
	setPresetParameter(preset->presetParameters, controlID::preampmute, -0.000000);
	addPreset(preset);

	// --- Preset: Pats Main Vocal
	preset = new PresetInfo(index++, "Pats Main Vocal");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::boxgain, 2.879999);
	setPresetParameter(preset->presetParameters, controlID::sharpgain, 3.120000);
	setPresetParameter(preset->presetParameters, controlID::airgain, 3.480000);
	setPresetParameter(preset->presetParameters, controlID::boxfc, 549.750000);
	setPresetParameter(preset->presetParameters, controlID::boxq, 5.820000);
	setPresetParameter(preset->presetParameters, controlID::inlvl, 5.639999);
	setPresetParameter(preset->presetParameters, controlID::outlvl, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::sharpfc, 2005.000000);
	setPresetParameter(preset->presetParameters, controlID::sharpq, 6.000000);
	setPresetParameter(preset->presetParameters, controlID::airfc, 13850.000000);
	setPresetParameter(preset->presetParameters, controlID::gatethresh, -46.800003);
	setPresetParameter(preset->presetParameters, controlID::gateattack, 1000.000000);
	setPresetParameter(preset->presetParameters, controlID::gaterelease, 671.000000);
	setPresetParameter(preset->presetParameters, controlID::gategain, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::compthresh, -23.040001);
	setPresetParameter(preset->presetParameters, controlID::compratio, 56.435001);
	setPresetParameter(preset->presetParameters, controlID::compattack, 617.500000);
	setPresetParameter(preset->presetParameters, controlID::comprelease, 486.999939);
	setPresetParameter(preset->presetParameters, controlID::compgain, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::verbgain, -36.300003);
	setPresetParameter(preset->presetParameters, controlID::delayfb, 40.000000);
	setPresetParameter(preset->presetParameters, controlID::delaytime, 185.000000);
	setPresetParameter(preset->presetParameters, controlID::drygain, -60.000000);
	setPresetParameter(preset->presetParameters, controlID::verbtime, 2260.000000);
	setPresetParameter(preset->presetParameters, controlID::preverbtime, 122.499985);
	setPresetParameter(preset->presetParameters, controlID::verbtime2, 0.735000);
	setPresetParameter(preset->presetParameters, controlID::delaydry, -60.000000);
	setPresetParameter(preset->presetParameters, controlID::delaywet, -24.600002);
	setPresetParameter(preset->presetParameters, controlID::eqmute, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::bpmdelay, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::prein, -3.000000);
	setPresetParameter(preset->presetParameters, controlID::presat, 1.190000);
	setPresetParameter(preset->presetParameters, controlID::preass, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::preout, -3.000000);
	setPresetParameter(preset->presetParameters, controlID::preampmute, -0.000000);
	addPreset(preset);


	// **--0xA7FF--**

    return true;
}

/**
\brief setup the plugin description strings, flags and codes; this is ordinarily done through the ASPiKreator or CMake

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginDescriptors()
{
    pluginDescriptor.pluginName = PluginCore::getPluginName();
    pluginDescriptor.shortPluginName = PluginCore::getShortPluginName();
    pluginDescriptor.vendorName = PluginCore::getVendorName();
    pluginDescriptor.pluginTypeCode = PluginCore::getPluginType();

	// --- describe the plugin attributes; set according to your needs
	pluginDescriptor.hasSidechain = kWantSidechain;
	pluginDescriptor.latencyInSamples = kLatencyInSamples;
	pluginDescriptor.tailTimeInMSec = kTailTimeMsec;
	pluginDescriptor.infiniteTailVST3 = kVSTInfiniteTail;

    // --- AAX
    apiSpecificInfo.aaxManufacturerID = kManufacturerID;
    apiSpecificInfo.aaxProductID = kAAXProductID;
    apiSpecificInfo.aaxBundleID = kAAXBundleID;  /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.aaxEffectID = "aaxDeveloper.";
    apiSpecificInfo.aaxEffectID.append(PluginCore::getPluginName());
    apiSpecificInfo.aaxPluginCategoryCode = kAAXCategory;

    // --- AU
    apiSpecificInfo.auBundleID = kAUBundleID;
	apiSpecificInfo.auBundleName = kAUBundleName;   /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.auBundleName = kAUBundleName;

    // --- VST3
    apiSpecificInfo.vst3FUID = PluginCore::getVSTFUID(); // OLE string format
    apiSpecificInfo.vst3BundleID = kVST3BundleID;/* MacOS only: this MUST match the bundle identifier in your info.plist file */
	apiSpecificInfo.enableVST3SampleAccurateAutomation = kVSTSAA;
	apiSpecificInfo.vst3SampleAccurateGranularity = kVST3SAAGranularity;

    // --- AU and AAX
    apiSpecificInfo.fourCharCode = PluginCore::getFourCharCode();

    return true;
}

// --- static functions required for VST3/AU only --------------------------------------------- //
const char* PluginCore::getPluginBundleName() { return kAUBundleName; }
const char* PluginCore::getPluginName(){ return kPluginName; }
const char* PluginCore::getShortPluginName(){ return kShortPluginName; }
const char* PluginCore::getVendorName(){ return kVendorName; }
const char* PluginCore::getVendorURL(){ return kVendorURL; }
const char* PluginCore::getVendorEmail(){ return kVendorEmail; }
const char* PluginCore::getAUCocoaViewFactoryName(){ return AU_COCOA_VIEWFACTORY_STRING; }
pluginType PluginCore::getPluginType(){ return kPluginType; }
const char* PluginCore::getVSTFUID(){ return kVSTFUID; }
int32_t PluginCore::getFourCharCode(){ return kFourCharCode; }
