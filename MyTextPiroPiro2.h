#pragma once

#include "ofEvents.h"

class MyTextPiroPiro2
{
public:
    MyTextPiroPiro2():
    mTargetStr(""),
    mCurrentStr(""),
    mStrIndex(0),
    mRange(0),
    mLastStoppedTimeMillis(0)
    {}
    
    MyTextPiroPiro2(const MyTextPiroPiro2 &mom)
    {
        assign(mom);
    }
    
    MyTextPiroPiro2 & operator=(const MyTextPiroPiro2 &mom)
    {
        assign(mom);
    }
    
    void assign(const MyTextPiroPiro2 &mom)
    {
        mTargetStr = mom.mTargetStr;
        mCurrentStr = mom.mCurrentStr;
        mStrIndex = mom.mStrIndex;
        mRange = mom.mRange;
        mIntervalMillis = mom.mIntervalMillis;
        mLastStoppedTimeMillis = mom.mLastStoppedTimeMillis;
    }
    
    ~MyTextPiroPiro2()
    {
        mTargetStr.clear();
        mCurrentStr.clear();
    }
    
    void setup(const string target)
    {
        mTargetStr = target;
        mCurrentStr.resize(mTargetStr.length(), ' ');
    }
    
    void update(ofEventArgs &e)
    {
        for (size_t i = mStrIndex; i < min(mStrIndex + mRange, mCurrentStr.length()); ++i) {
            mCurrentStr[i] = static_cast<char>(floor(ofRandom(33, 127)));
        }
        
        if (mIntervalMillis < ofGetElapsedTimeMillis() - mLastStoppedTimeMillis) {
            mCurrentStr[mStrIndex] = mTargetStr[mStrIndex];
            mLastStoppedTimeMillis = ofGetElapsedTimeMillis();
            
            if (++mStrIndex > mTargetStr.length()) {
                ofRemoveListener(ofEvents().update, this, &MyTextPiroPiro2::update);
                mRange = 0;
            }
        }
    }
    
    void play(const size_t range = 0, const double durationMillis = 1000, const double delayMillis = 0)
    {
        mRange = 0 == range ? mTargetStr.length() : range;
        mIntervalMillis = durationMillis / mTargetStr.length();ofLog() << mIntervalMillis;
        mLastStoppedTimeMillis = ofGetElapsedTimeMillis() + delayMillis;
        mCurrentStr.clear();
        mCurrentStr.resize(mTargetStr.length(), ' ');
        mStrIndex = 0;
        
        ofAddListener(ofEvents().update, this, &MyTextPiroPiro2::update);
    }
    
    const string & get()
    {
        return mCurrentStr;
    }
    
private:
    string mTargetStr, mCurrentStr;
    size_t mStrIndex, mRange;
    double mIntervalMillis, mLastStoppedTimeMillis;
};