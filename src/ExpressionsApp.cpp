#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "OscListener.h"
#include "ExpressionClassifier.h"
#include "Expression.h"
#include "ciUI.h"
#include "cinderSyphon.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ExpressionsApp : public AppBasic {
    public:
        ExpressionsApp(){}
        ~ExpressionsApp();
        void setup();
        void mouseDown( MouseEvent event );
        void update();
        void draw();
    
        void guiEvent(ciUIEvent *event);
        
        syphonClient    mClientSyphon;
        osc::Listener   mListener;
        ciUICanvas      *mGui;
        bool            mSaveExpression;
        ExpressionClassifier mClassifier;
        Expression      mCurrentExpression;
        std::string     mExpressionName;
    
        ciUISlider      *mMouthWidthSldr,
        *mMouthHeightSldr,
        *mEyebrowLeftSldr,
        *mEyebrowRightSldr,
        *mEyeLeftSldr,
        *mEyeRightSldr,
        *mJawSldr,
        *mNostrilsSldr;
    
        ciUITextInput   *mDescField;
};

void ExpressionsApp::setup()
{
    std::string appPath = ci::app::getAppPath().string();
    std::string faceOSCCmd = "open " + appPath + "/Contents/Resources/FaceOSCSyphon.app --background";
    
    std::system(faceOSCCmd.c_str());
    
    mClientSyphon.setup();
    mClientSyphon.setApplicationName("FaceOSC");
    mClientSyphon.setServerName("");
    mClientSyphon.bind();
    
    mListener.setup(8338);
    mSaveExpression = false;
    mExpressionName = "Expression Name";
    
    mClassifier.setup(appPath);
    
    mGui = new ciUICanvas();
    mGui->addWidgetDown(new ciUILabel("EXPRESSION CLASSIFIER TRAINING", CI_UI_FONT_SMALL));
    mMouthWidthSldr     = (ciUISlider*)mGui->addWidgetDown(new ciUISlider(240, 20, 0.0f, 15.0f, &mCurrentExpression.mMouthWidth, "Mouth width"));
    mMouthHeightSldr    = (ciUISlider*)mGui->addWidgetDown(new ciUISlider(240, 20, 0.0f, 10.0f, &mCurrentExpression.mMouthHeight, "Mouth height"));
    mEyebrowLeftSldr    = (ciUISlider*)mGui->addWidgetDown(new ciUISlider(240, 20, 5.0f, 15.0f, &mCurrentExpression.mEyebrowLeft, "Left eyebrow"));
    mEyebrowRightSldr   = (ciUISlider*)mGui->addWidgetDown(new ciUISlider(240, 20, 5.0f, 15.0f, &mCurrentExpression.mEyebrowRight, "Right eyebrow"));
    mEyeLeftSldr        = (ciUISlider*)mGui->addWidgetDown(new ciUISlider(240, 20, 0.0f, 5.0f, &mCurrentExpression.mEyeLeft, "Left eye"));
    mEyeRightSldr       = (ciUISlider*)mGui->addWidgetDown(new ciUISlider(240, 20, 0.0f, 5.0f, &mCurrentExpression.mEyeRight, "Right eye"));
    mJawSldr            = (ciUISlider*)mGui->addWidgetDown(new ciUISlider(240, 20, 15.0f, 25.0f, &mCurrentExpression.mJaw, "Jaw"));
    mNostrilsSldr       = (ciUISlider*)mGui->addWidgetDown(new ciUISlider(240, 20, 3.0f, 9.0f, &mCurrentExpression.mNostrils, "Nostrils"));
    
    mDescField = (ciUITextInput*)mGui->addWidgetRight(new ciUITextInput(240, "Name", "Expression name", CI_UI_FONT_SMALL));
    mGui->addWidgetRight(new ciUILabelButton(&mSaveExpression, "Save", CI_UI_FONT_SMALL));
    
    mGui->autoSizeToFitWidgets();
    mGui->registerUIEvents(this, &ExpressionsApp::guiEvent);
}

void ExpressionsApp::mouseDown( MouseEvent event )
{
}

void ExpressionsApp::update()
{
    if (mSaveExpression) {
        
        mCurrentExpression.setDescription(mDescField->getTextString());
        mCurrentExpression.save();
        
    }
    
    while (mListener.hasWaitingMessages()) {
		
        osc::Message message;
        
		mListener.getNextMessage(&message);
        
        if ("/gesture/mouth/width" == message.getAddress()) {
            mCurrentExpression.updateMouthWidth(message.getArgAsFloat(0));
            mMouthWidthSldr->updateLabel();
            mClassifier.classify(&mCurrentExpression);
            // TODO don't just call this here
        }
        else if ("/gesture/mouth/height" == message.getAddress()) {
            mCurrentExpression.updateMouthHeight(message.getArgAsFloat(0));
            mMouthHeightSldr->updateLabel();
        }
        else if ("/gesture/eyebrow/left" == message.getAddress()) {
            mCurrentExpression.updateEyebrowLeft(message.getArgAsFloat(0));
            mEyebrowLeftSldr->updateLabel();
        }
        else if ("/gesture/eyebrow/right" == message.getAddress()) {
            mCurrentExpression.updateEyebrowRight(message.getArgAsFloat(0));
            mEyebrowRightSldr->updateLabel();
        }
        else if ("/gesture/eye/left" == message.getAddress()) {
            mCurrentExpression.updateEyeLeft(message.getArgAsFloat(0));
            mEyeLeftSldr->updateLabel();
        }
        else if ("/gesture/eye/right" == message.getAddress()) {
            mCurrentExpression.updateEyeRight(message.getArgAsFloat(0));
            mEyeRightSldr->updateLabel();
        }
        else if ("/gesture/jaw" == message.getAddress()) {
            mCurrentExpression.updateJaw(message.getArgAsFloat(0));
            mJawSldr->updateLabel();
        }
        else if ("/gesture/nostrils" == message.getAddress()) {
            mCurrentExpression.updateNostrils(message.getArgAsFloat(0));
            mNostrilsSldr->updateLabel();
        }
        
    }
    
    mGui->update();
}

void ExpressionsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    mClientSyphon.draw(0,0, 640, 480);
    mGui->draw();
}

void ExpressionsApp::guiEvent(ciUIEvent *event)
{
    
}

ExpressionsApp::~ExpressionsApp()
{
    delete mGui;
    std::system("killall FaceOSC");
}

CINDER_APP_BASIC( ExpressionsApp, RendererGl )
