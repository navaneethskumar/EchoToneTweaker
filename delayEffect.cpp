/*
  ==============================================================================

    delayEffect.cpp
    Created: 16 Sep 2023 1:29:07pm
    Author:  Navaneeth Suresh Kumar

  ==============================================================================
*/

#include "delayEffect.h"
delayEffect::delayEffect() {
    //

    readIndexL = 0;
    readIndexR = 0;
    writeIndexL = 0;
    writeIndexR = 0;
    delayBufferSize = 0;
    bufferSize = 0;
    totalNumInputChannels = 0;

    //
}
delayEffect::~delayEffect() {

    //
}
void delayEffect::prepareToPlay(float sampleRate, int samplesPrerBlock, int numInputChannels)
{

    bufferSize = sampleRate * 2;
    this->totalNumInputChannels = numInputChannels;
    delayBufferLeft.resize(bufferSize, 0.0f);
    delayBufferRight.resize(bufferSize, 0.0f);


}

void delayEffect::circularBuffer(juce::AudioBuffer<float>& buffer, float delayLength, float feedback, float dryWet) {

    /*auto delayLength = sampleRate * 1.0;*/
//auto delayBufferSize = delayLength + buffer.getNumSamples();
    //delayBufferSize = delayBufferSize * totalNumInputChannels;
    //delayBuffer.resize(delayBufferSize, 0.f);
    readIndexL = writeIndexL - delayLength ;
    if (readIndexL < 0)
        readIndexL = bufferSize + readIndexL;
    readIndexR = writeIndexR - delayLength ;
    if (readIndexR < 0)
        readIndexR = bufferSize + readIndexR;


    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        
        

            for (int n = 0; n < buffer.getNumSamples(); n++) {

               
                delayBufferLeft[writeIndexL] = buffer.getSample(channel, n) + delayBufferLeft[readIndexL] * (feedback/100);
                buffer.getWritePointer(channel)[n] = buffer.getSample(channel, n) * (1 - dryWet/100) + delayBufferLeft[writeIndexL] * dryWet/100;
                //readIndexL += 1;
                //writeIndexL += 1;
                readIndexL = (readIndexL + 1) % delayBufferLeft.size();
                writeIndexL = (writeIndexL + 1) % delayBufferLeft.size();


            }

        
        

            for (int n = 0; n < buffer.getNumSamples(); n++) {

                delayBufferRight[writeIndexR] = buffer.getSample(channel, n) + delayBufferRight[readIndexR] * (feedback/100);
                buffer.getWritePointer(channel)[n] = buffer.getSample(channel, n) * (1 - dryWet/100) + delayBufferRight[writeIndexR] * dryWet/100;
                    writeIndexR = (writeIndexR + 1 )% delayBufferRight.size();
           

                    readIndexR = ( readIndexR + 1 )% delayBufferRight.size();
                    



            }
        
        
    }



};
