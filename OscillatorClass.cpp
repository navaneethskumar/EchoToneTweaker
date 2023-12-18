/*
  ==============================================================================

    OscillatorClass.cpp
    Created: 6 Oct 2023 1:23:44pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#include "OscillatorClass.h"
OscillatorClass::OscillatorClass() {
    //


    bufferSize = 0 ;
    bufferIndex = 0;
    modVal = -1;
    modSquareVal = 1;
    Fo = 300.0;
    gain = 0.7;
    onOff = false;

    //
}
OscillatorClass::~OscillatorClass() {

    //
}
void OscillatorClass::prepareToPlay(float sampleRate, int samplesPrerBlock, int numInputChannels)
{

    bufferSize = sampleRate * 2;
    this->totalNumInputChannels = numInputChannels;
    BufferLeft.resize(bufferSize, 0.0f);
    BufferRight.resize(bufferSize, 0.0f);


}
void OscillatorClass::setOscillatorState(bool newState) {
    onOff = newState;
}
void OscillatorClass::oscillator(juce::AudioBuffer<float>& buffer, double fs, int x) {
    
    /*auto delayLength = sampleRate * 1.0;*/
    //auto delayBufferSize = delayLength + buffer.getNumSamples();
    //delayBufferSize = delayBufferSize * totalNumInputChannels;
    //delayBuffer.resize(delayBufferSize, 0.f);

    if(onOff){
        
        
        for (int bufferIndex = 0; bufferIndex < buffer.getNumSamples(); bufferIndex++){
            
            
            
        
            modVal += (Fo / (fs));
            if (modVal > 1.0f)
            {
                modVal -= 1.0f;
                modSquareVal *= -1.0f;
            }
            //  moduloCounter(modVal, modSquareVal, Fo, fs);
            switch (x)
            {
                case 0: // Sinusoidal
                    BufferLeft[bufferIndex] = gain * std::sin(2.0 * juce::MathConstants<float>::pi * modVal);
                    BufferRight[bufferIndex] =  gain * std::sin(2.0 * juce::MathConstants<float>::pi * modVal);
                    break;
                case 1: // sawtooth
                    BufferLeft[bufferIndex] = gain * modVal;
                    BufferRight[bufferIndex] = gain * modVal;
                    break;
                case 2: // Triangle
                    BufferLeft[bufferIndex] = gain * (2.0f * std::abs(modVal) - 1.0f);
                    BufferRight[bufferIndex]= gain * (2.0f * std::abs(modVal) - 1.0f);
                    break;
                case 3: // Sawtooth

                    BufferLeft[bufferIndex] = gain * modSquareVal;
                    BufferRight[bufferIndex] = gain * modSquareVal;
                    break;
                default:
                    break;
            }
            //buffer.getWritePointer(0)[bufferIndex] = BufferLeft[bufferIndex];
            //buffer.getWritePointer(1)[bufferIndex] = BufferRight[bufferIndex];
            buffer.setSample(0, bufferIndex, BufferLeft[bufferIndex]);
            buffer.setSample(1, bufferIndex, BufferRight[bufferIndex]);
        }
        //
    }

}

//void OscillatorClass::moduloCounter(float modVal, float modSquareVal, double Fo, double sampleRate)
//{
//    modVal += (Fo / sampleRate);
//    if (modVal > 1.0)
//    {
//        modVal -= 2.0;
//        modSquareVal *= -1.0;
//    }
//}
