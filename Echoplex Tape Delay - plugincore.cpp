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
#include "tapedelay.h"
#include "delaymod.h"


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

	// --- continuous control: HP Cutoff
	piParam = new PluginParameter(controlID::bandLimitHPFFc_Hz, "HP Cutoff", "Hz", controlVariableType::kDouble, 20.000000, 1000.000000, 20.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&bandLimitHPFFc_Hz, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LP Cutoff
	piParam = new PluginParameter(controlID::bandLimitLPFFc_Hz, "LP Cutoff", "Hz", controlVariableType::kDouble, 8000.000000, 20000.000000, 8000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&bandLimitLPFFc_Hz, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Threshold
	piParam = new PluginParameter(controlID::limiterThreshold_dB, "Threshold", "dB", controlVariableType::kDouble, -3.000000, -24.000000, -24.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&limiterThreshold_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Make Up Gain
	piParam = new PluginParameter(controlID::limiterMakeUpGain_dB, "Make Up Gain", "dB", controlVariableType::kDouble, 0.000000, 10.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&limiterMakeUpGain_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Record Level
	piParam = new PluginParameter(controlID::recordLevel_dB, "Record Level", "dB", controlVariableType::kDouble, 0.000000, 10.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&recordLevel_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Playback Level
	piParam = new PluginParameter(controlID::playbackLevel_dB, "Playback Level", "dB", controlVariableType::kDouble, 0.000000, 10.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&playbackLevel_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Dry Gain
	piParam = new PluginParameter(controlID::drygain, "Dry Gain", "dB", controlVariableType::kDouble, 0.000000, 10.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&drygain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Feedback
	piParam = new PluginParameter(controlID::feebackpercent, "Feedback", "%", controlVariableType::kDouble, 0.000000, 100.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&feebackpercent, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO 1 Freq
	piParam = new PluginParameter(controlID::lfo1freq, "LFO 1 Freq", "Hz", controlVariableType::kDouble, 2.500000, 500.000000, 2.500000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&lfo1freq, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO 2 Freq
	piParam = new PluginParameter(controlID::lfo2freq, "LFO 2 Freq", "Hz", controlVariableType::kDouble, 5.000000, 500.000000, 5.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&lfo2freq, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO 3 Freq
	piParam = new PluginParameter(controlID::lfo3freq, "LFO 3 Freq", "Hz", controlVariableType::kDouble, 26.000000, 500.000000, 26.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&lfo3freq, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO 1 Gain
	piParam = new PluginParameter(controlID::lfo1gain, "LFO 1 Gain", "", controlVariableType::kDouble, 0.000000, 10.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&lfo1gain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO 2 Gain
	piParam = new PluginParameter(controlID::lfo2gain, "LFO 2 Gain", "", controlVariableType::kDouble, 0.000000, 10.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&lfo2gain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO 3 Gain
	piParam = new PluginParameter(controlID::lfo3gain, "LFO 3 Gain", "", controlVariableType::kDouble, 0.000000, 10.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&lfo3gain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO Depth
	piParam = new PluginParameter(controlID::lfodepth, "LFO Depth", "%", controlVariableType::kDouble, 0.000000, 100.000000, 50.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&lfodepth, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Noise Cutoff
	piParam = new PluginParameter(controlID::noisefc, "Noise Cutoff", "Hz", controlVariableType::kDouble, 0.000000, 100.000000, 50.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&noisefc, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Noise Gain
	piParam = new PluginParameter(controlID::noisegain, "Noise Gain", "", controlVariableType::kDouble, 0.000000, 10.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&noisegain, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Delay Time
	piParam = new PluginParameter(controlID::delaytime, "Delay Time", "ms", controlVariableType::kDouble, 90.000000, 680.000000, 90.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&delaytime, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Saturation
	piParam = new PluginParameter(controlID::waveshaperSaturation, "Saturation", "", controlVariableType::kDouble, 0.000000, 20.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&waveshaperSaturation, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: System Noise Gain
	piParam = new PluginParameter(controlID::sixtyHzNoiseAmplitude, "System Noise Gain", "", controlVariableType::kDouble, 0.000000, 10.000000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&sixtyHzNoiseAmplitude, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Tape Cutoff
	piParam = new PluginParameter(controlID::tapeNoiseFc_Hz, "Tape Cutoff", "Hz", controlVariableType::kDouble, 20.000000, 20000.000000, 10000.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&tapeNoiseFc_Hz, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Tape Gain
	piParam = new PluginParameter(controlID::tapeNoiseAmplitude, "Tape Gain", "", controlVariableType::kDouble, 0.000000, 2.500000, 1.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&tapeNoiseAmplitude, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: Output Gain
	piParam = new PluginParameter(controlID::outputAmplitude_dB, "Output Gain", "dB", controlVariableType::kDouble, -40.000000, 12.000000, -40.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&outputAmplitude_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- Aux Attributes
	AuxParameterAttribute auxAttribute;

	// --- RAFX GUI attributes
	// --- controlID::bandLimitHPFFc_Hz
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::bandLimitHPFFc_Hz, auxAttribute);

	// --- controlID::bandLimitLPFFc_Hz
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::bandLimitLPFFc_Hz, auxAttribute);

	// --- controlID::limiterThreshold_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::limiterThreshold_dB, auxAttribute);

	// --- controlID::limiterMakeUpGain_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::limiterMakeUpGain_dB, auxAttribute);

	// --- controlID::recordLevel_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::recordLevel_dB, auxAttribute);

	// --- controlID::playbackLevel_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::playbackLevel_dB, auxAttribute);

	// --- controlID::drygain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::drygain, auxAttribute);

	// --- controlID::feebackpercent
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::feebackpercent, auxAttribute);

	// --- controlID::lfo1freq
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::lfo1freq, auxAttribute);

	// --- controlID::lfo2freq
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::lfo2freq, auxAttribute);

	// --- controlID::lfo3freq
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::lfo3freq, auxAttribute);

	// --- controlID::lfo1gain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::lfo1gain, auxAttribute);

	// --- controlID::lfo2gain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::lfo2gain, auxAttribute);

	// --- controlID::lfo3gain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::lfo3gain, auxAttribute);

	// --- controlID::lfodepth
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::lfodepth, auxAttribute);

	// --- controlID::noisefc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::noisefc, auxAttribute);

	// --- controlID::noisegain
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::noisegain, auxAttribute);

	// --- controlID::delaytime
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::delaytime, auxAttribute);

	// --- controlID::waveshaperSaturation
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::waveshaperSaturation, auxAttribute);

	// --- controlID::sixtyHzNoiseAmplitude
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::sixtyHzNoiseAmplitude, auxAttribute);

	// --- controlID::tapeNoiseFc_Hz
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::tapeNoiseFc_Hz, auxAttribute);

	// --- controlID::tapeNoiseAmplitude
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::tapeNoiseAmplitude, auxAttribute);

	// --- controlID::outputAmplitude_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::outputAmplitude_dB, auxAttribute);


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

	EchoPlexTapeDelayParameters delayparams = tapedelay.getParameters();
	tapedelay.setParameters(delayparams);
	tapedelay.reset(resetInfo.sampleRate);

	EchoplexDelayModulatorParameters modparams = delaymod.getParameters();
	delaymod.setParameters(modparams);
	delaymod.reset(resetInfo.sampleRate);

	tapedelay.createDelayBuffers(resetInfo.sampleRate, 590);


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

void PluginCore::UpdateParameters()
{
	EchoplexDelayModulatorParameters modparams = delaymod.getParameters();
	modparams.delayTime = delaytime;
	modparams.lfo1Amplitude = lfo1gain;
	modparams.lfo1Frequency_Hz = lfo1freq;
	modparams.lfo2Amplitude = lfo2gain;
	modparams.lfo2Frequency_Hz = lfo2freq;
	modparams.lfo3Amplitude = lfo3gain;
	modparams.lfo3Frequency_Hz = lfo3freq;
	modparams.lfoDepth_Pct = lfodepth;
	modparams.noiseFilterFc_Hz = noisefc;
	modparams.noiseFilterAmplitude = noisegain;
	delaymod.setParameters(modparams);

	SignalGenData xdelaymod;
	xdelaymod = delaymod.renderAudioOutput();

	EchoPlexTapeDelayParameters delayparams = tapedelay.getParameters();
	delayparams.bandLimitHPFFc_Hz = bandLimitHPFFc_Hz;
	delayparams.bandLimitLPFFc_Hz = bandLimitLPFFc_Hz;
	delayparams.limiterThreshold_dB = limiterThreshold_dB;
	delayparams.limiterMakeUpGain_dB = limiterMakeUpGain_dB;
	delayparams.recordLevel_dB = recordLevel_dB;
	delayparams.playbackLevel_dB = playbackLevel_dB;
	delayparams.waveshaperSaturation = waveshaperSaturation;
	delayparams.tapeNoiseAmplitude = tapeNoiseAmplitude;
	delayparams.tapeNoiseFc_Hz = tapeNoiseFc_Hz;
	delayparams.sixtyHzNoiseAmplitude = sixtyHzNoiseAmplitude;
	delayparams.outputAmplitude_dB = outputAmplitude_dB;
	delayparams.drygain = drygain;
	delayparams.feedbackpercent = feebackpercent;
	delayparams.leftDelay_mSec = xdelaymod.normalOutput;
	delayparams.rightDelay_mSec = xdelaymod.normalOutput;
	tapedelay.setParameters(delayparams);

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
	UpdateParameters();

	/*
	double yn = 0.0;
	SignalGenData x = delaymod.renderAudioOutput();
	yn = x.normalOutput;
	*/

	tapedelay.processAudioFrame(processFrameInfo.audioInputFrame, processFrameInfo.audioOutputFrame, processFrameInfo.numAudioInChannels, processFrameInfo.numAudioOutChannels);

    // --- FX Plugin:
    if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFMono)
    {
		// --- pass through code: change this with your signal processing
		processFrameInfo.audioOutputFrame[0] = outputFrame[0]; // processFrameInfo.audioInputFrame[0];

        return true; /// processed
    }

    // --- Mono-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFMono &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
		processFrameInfo.audioOutputFrame[0] = outputFrame[0];  // processFrameInfo.audioInputFrame[0];
		processFrameInfo.audioOutputFrame[1] = outputFrame[0]; // processFrameInfo.audioInputFrame[0];

        return true; /// processed
    }

    // --- Stereo-In/Stereo-Out
    else if(processFrameInfo.channelIOConfig.inputChannelFormat == kCFStereo &&
       processFrameInfo.channelIOConfig.outputChannelFormat == kCFStereo)
    {
		// --- pass through code: change this with your signal processing
		processFrameInfo.audioOutputFrame[0] = outputFrame[0]; // processFrameInfo.audioInputFrame[0];
		processFrameInfo.audioOutputFrame[1] = outputFrame[1]; // processFrameInfo.audioInputFrame[1];

        return true; /// processed
    }

    return false; /// NOT processed
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
	setPresetParameter(preset->presetParameters, controlID::bandLimitHPFFc_Hz, 20.000000);
	setPresetParameter(preset->presetParameters, controlID::bandLimitLPFFc_Hz, 8000.000000);
	setPresetParameter(preset->presetParameters, controlID::limiterThreshold_dB, -24.000000);
	setPresetParameter(preset->presetParameters, controlID::limiterMakeUpGain_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::recordLevel_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::playbackLevel_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::drygain, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::feebackpercent, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1freq, 2.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2freq, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo3freq, 26.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1gain, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2gain, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo3gain, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::lfodepth, 50.000000);
	setPresetParameter(preset->presetParameters, controlID::noisefc, 50.000000);
	setPresetParameter(preset->presetParameters, controlID::noisegain, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::delaytime, 90.000000);
	setPresetParameter(preset->presetParameters, controlID::waveshaperSaturation, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::sixtyHzNoiseAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::tapeNoiseFc_Hz, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::tapeNoiseAmplitude, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::outputAmplitude_dB, -40.000000);
	addPreset(preset);

	// --- Preset: Preset 1
	preset = new PresetInfo(index++, "Preset 1");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::bandLimitHPFFc_Hz, 402.199982);
	setPresetParameter(preset->presetParameters, controlID::bandLimitLPFFc_Hz, 8000.000000);
	setPresetParameter(preset->presetParameters, controlID::limiterThreshold_dB, -24.000000);
	setPresetParameter(preset->presetParameters, controlID::limiterMakeUpGain_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::recordLevel_dB, 3.650000);
	setPresetParameter(preset->presetParameters, controlID::playbackLevel_dB, 2.750000);
	setPresetParameter(preset->presetParameters, controlID::drygain, 5.100000);
	setPresetParameter(preset->presetParameters, controlID::feebackpercent, 26.499998);
	setPresetParameter(preset->presetParameters, controlID::lfo1freq, 2.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2freq, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo3freq, 26.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1gain, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo2gain, 1.100000);
	setPresetParameter(preset->presetParameters, controlID::lfo3gain, 0.650000);
	setPresetParameter(preset->presetParameters, controlID::lfodepth, 14.000000);
	setPresetParameter(preset->presetParameters, controlID::noisefc, 50.000000);
	setPresetParameter(preset->presetParameters, controlID::noisegain, 1.000000);
	setPresetParameter(preset->presetParameters, controlID::delaytime, 317.149994);
	setPresetParameter(preset->presetParameters, controlID::waveshaperSaturation, 23.500000);
	setPresetParameter(preset->presetParameters, controlID::sixtyHzNoiseAmplitude, 4.250000);
	setPresetParameter(preset->presetParameters, controlID::tapeNoiseFc_Hz, 10000.000000);
	setPresetParameter(preset->presetParameters, controlID::tapeNoiseAmplitude, 1.050000);
	setPresetParameter(preset->presetParameters, controlID::outputAmplitude_dB, -40.000000);
	addPreset(preset);

	// --- Preset: START 
	preset = new PresetInfo(index++, "START ");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::bandLimitHPFFc_Hz, 299.299988);
	setPresetParameter(preset->presetParameters, controlID::bandLimitLPFFc_Hz, 8000.000000);
	setPresetParameter(preset->presetParameters, controlID::limiterThreshold_dB, -20.430000);
	setPresetParameter(preset->presetParameters, controlID::limiterMakeUpGain_dB, 0.700000);
	setPresetParameter(preset->presetParameters, controlID::recordLevel_dB, 2.100000);
	setPresetParameter(preset->presetParameters, controlID::playbackLevel_dB, 2.100000);
	setPresetParameter(preset->presetParameters, controlID::drygain, 4.950000);
	setPresetParameter(preset->presetParameters, controlID::feebackpercent, 23.500002);
	setPresetParameter(preset->presetParameters, controlID::lfo1freq, 2.500000);
	setPresetParameter(preset->presetParameters, controlID::lfo2freq, 5.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo3freq, 26.000000);
	setPresetParameter(preset->presetParameters, controlID::lfo1gain, 1.450000);
	setPresetParameter(preset->presetParameters, controlID::lfo2gain, 2.050000);
	setPresetParameter(preset->presetParameters, controlID::lfo3gain, 2.250000);
	setPresetParameter(preset->presetParameters, controlID::lfodepth, 8.500002);
	setPresetParameter(preset->presetParameters, controlID::noisefc, 19.500000);
	setPresetParameter(preset->presetParameters, controlID::noisegain, 2.700000);
	setPresetParameter(preset->presetParameters, controlID::delaytime, 90.000000);
	setPresetParameter(preset->presetParameters, controlID::waveshaperSaturation, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::sixtyHzNoiseAmplitude, 4.500000);
	setPresetParameter(preset->presetParameters, controlID::tapeNoiseFc_Hz, 12897.099609);
	setPresetParameter(preset->presetParameters, controlID::tapeNoiseAmplitude, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::outputAmplitude_dB, -40.000000);
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
