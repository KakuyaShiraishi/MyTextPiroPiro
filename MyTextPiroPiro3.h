#pragma once

#include "ofEvents.h"

class MyTextPiroPiro3
{
public:
    
    MyTextPiroPiro3():
    mTargetStr(),
    mCurrentStr(),
    mStrIndex(0),
    mRange(0),
    mLastStoppedTimeMillis(0)
    {
    }
    
    MyTextPiroPiro3(const string target):
    mTargetStr(target),
    mCurrentStr(),
    mStrIndex(0),
    mRange(0),
    mLastStoppedTimeMillis(0)
    {
    }
    
    MyTextPiroPiro3(const MyTextPiroPiro3 &mom)
    {
        _assign(mom);
    }
    
    MyTextPiroPiro3 & operator=(const MyTextPiroPiro3 &mom)
    {
        _assign(mom);
        return *this;
    }
    
    MyTextPiroPiro3 & operator+=(const MyTextPiroPiro3 &str)
    {
        setup(mTargetStr + str.mTargetStr);
        return *this;
    }
    
    string & operator=(const string &str)
    {
        setup(str);
        return mTargetStr;
    }
    
    string & operator+=(const string &str)
    {
        setup(mTargetStr + str);
        return mTargetStr;
    }
    
    friend ostream & operator<<(ostream &os, const MyTextPiroPiro3 &str)
    {
        os << str.mTargetStr;
        return os;
    }
    
    operator string()
    {
        return mCurrentStr;
    }
    
    ~MyTextPiroPiro3()
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
                ofRemoveListener(ofEvents().update, this, &MyTextPiroPiro3::update);
                mRange = 0;
            }
        }
    }
    
    void play(const size_t range = 0, const double durationMillis = 1000, const double delayMillis = 0)
    {
        mRange = 0 == range ? mTargetStr.length() : range;
        
        mIntervalMillis = durationMillis / mTargetStr.length(); ofLog() << mIntervalMillis;
        mLastStoppedTimeMillis = ofGetElapsedTimeMillis() + delayMillis;
        
        mCurrentStr.clear();
        mCurrentStr.resize(mTargetStr.length(), ' ');
        mStrIndex = 0;
        
        ofAddListener(ofEvents().update, this, &MyTextPiroPiro3::update);
    }
    
    const string & get()
    {
        return mCurrentStr;
    }
    
private:
    
    void _assign(const MyTextPiroPiro3 &mom)
    {
        mTargetStr = mom.mTargetStr;
        mCurrentStr = mom.mCurrentStr;
        mStrIndex = mom.mStrIndex;
        mRange = mom.mRange;
        mIntervalMillis = mom.mIntervalMillis;
        mLastStoppedTimeMillis = mom.mLastStoppedTimeMillis;
    }
    
    string mTargetStr, mCurrentStr;
    size_t mStrIndex, mRange;
    double mIntervalMillis, mLastStoppedTimeMillis;
};