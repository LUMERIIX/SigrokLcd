/***************************************************************
 * Name:      SigrokLcdMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2017-05-31
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef SIGROKLCDMAIN_H
#define SIGROKLCDMAIN_H

class wxLCDWindow;
class awxLed;

#include <libsigrokcxx/libsigrokcxx.hpp>
#include "lcdwindow.h"
#include "led.h"

#include <wx/combobox.h>

//#include <wx/thread.h>
//#include <wx/event.h>
//#include "lcdwindow.h"
//#include "led.h"

//(*Headers(LcdTestFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
//*)

//wxDECLARE_EVENT(wxEVT_COMMAND_MYTHREAD_COMPLETED, wxThreadEvent);
//wxDECLARE_EVENT(wxEVT_COMMAND_MYTHREAD_UPDATE, wxThreadEvent);
//class SigrokLcdFrame;

//class MyThread : public wxThread
//{
//    public:
//        MyThread(SigrokLcdFrame *handler) : wxThread(wxTHREAD_DETACHED)
//        {
//            m_pHandler = handler;
//        }
//        ~MyThread();
//    protected:
//        virtual ExitCode Entry();
//        SigrokLcdFrame *m_pHandler;
//};

class SigrokLcdFrame: public wxFrame//, public wxThreadHelper
{
    public:

         SigrokLcdFrame(wxWindow* parent,wxWindowID id = -1);
       virtual  ~SigrokLcdFrame();
       void RefreshParameters(wxKeyEvent& event);
//        void DoStartThread();
//        void DoPauseThread();
        // a resume routine would be nearly identic to DoPauseThread()
        //void DoResumeThread() { ... }
//        void OnThreadUpdate(wxThreadEvent& evt);
//        void DoStartALongTask();
//        void OnClose(wxCloseEvent& evt);


    private:
        wxLCDWindow *lcd_;
        awxLed *ledmHz_;
        awxLed *ledHz_;
        awxLed *ledkHz_;
        awxLed *ledMHz_;
        uint8_t ledState_;
        uint64_t samplerate;

        wxComboBox* ChannelSelect;
        wxComboBox* RefChannelSelect;
        wxComboBox* GateTime;

        std::string Timebase;
        std::string MeasChannel;
        std::string RefChannel;

        std::shared_ptr<sigrok::Context> context_;
        std::shared_ptr<sigrok::Session> session_;
        std::shared_ptr<sigrok::HardwareDevice> hwDev;
        void sigrok_datafeed_callback(std::shared_ptr<sigrok::Device> hwDev, std::shared_ptr<sigrok::Packet> packet);
        void sigrok_stopped_callback();
                wxDECLARE_EVENT_TABLE();

    //protected:
//        virtual wxThread::ExitCode sigrok_datafeed_callback(std::shared_ptr<sigrok::Device> hwDev, std::shared_ptr<sigrok::Packet> packet);
//        wxCriticalSection m_dataCS;

//        wxDECLARE_EVENT_TABLE();



        //(*Handlers(LcdTestFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnConnect(wxCommandEvent& event);
        void OnDisconnect(wxCommandEvent& event);
        void OnCalib(wxCommandEvent& event);
        void OnSetup(wxCommandEvent& event);
        void OnMeasure(wxCommandEvent& event);
        //*)

        //(*Identifiers(LcdTestFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long idMenuConnect;
        static const long idMenuDisconnect;
        static const long idMenuCalibration;

        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(LcdTestFrame)
        wxStatusBar* StatusBar1;
        //*)


};
//void SigrokLcdFrame::DoStartALongTask()
//{
//    // we want to start a long task, but we don't want our GUI to block
//    // while it's executed, so we use a thread to do it.
//    if (CreateThread(wxTHREAD_JOINABLE) != wxTHREAD_NO_ERROR)
//    {
//        wxLogError("Could not create the worker thread!");
//        return;
//    }
//    // go!
//    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
//    {
//        wxLogError("Could not run the worker thread!");
//        return;
//    }
//}
//wxThread::ExitCode SigrokLcdFrame::sigrok_datafeed_callback(std::shared_ptr<sigrok::Device> hwDev, std::shared_ptr<sigrok::Packet> packet)
//{
//    float f;
//    int i = 0;
//    float exp_val = 0;
//    float exp =1;
//    float disp_val = 0;
//
//    while (!GetThread()->TestDestroy())
//    {
//
//        //::wxMessageBox("sigrok_datafeed_callback");
//        if(packet->type() == sigrok::PacketType::ANALOG)
//        {
//            std::shared_ptr<sigrok::Analog> analogPacket = std::dynamic_pointer_cast<sigrok::Analog>(packet->payload());
//            analogPacket->get_data_as_float(&f);
//
//            ledmHz_->SetState(awxLED_OFF);
//            ledHz_->SetState(awxLED_OFF);
//            ledkHz_->SetState(awxLED_OFF);
//            ledMHz_->SetState(awxLED_OFF);
//
//            exp_val = (log10(f));
//
//            wxString expval = wxString::Format(_T("%10.6f"), exp_val);
//            wxString getfloat = wxString::Format(_T("%10.6f"), f);
//            //::wxMessageBox("exp: %s",getfloat);
//
//            if(exp_val >= 6.0000)
//            {
//                    exp_val = 6;
//                    ledMHz_->SetState(awxLED_ON);
//            }
//            else if(exp_val >= 3.00000)
//            {
//                    exp_val = 3;
//                    ledkHz_->SetState(awxLED_ON);
//            }
//            else if(exp_val >= 0.00000)
//            {
//                    exp_val = 0;
//                    ledHz_->SetState(awxLED_ON);
//            }
//            else if(exp_val >= -3.00000)
//            {
//                    exp_val = -3;
//                    ledmHz_->SetState(awxLED_ON);
//            }
//
//            if(f<=0)
//            {
//                exp_val = 0;
//                ledHz_->SetState(awxLED_ON);
//            }
//
//            disp_val = f / pow(10,exp_val);
//
//            wxString nextVal = wxString::Format(_T("%10.4f"), disp_val);
//            //::wxMessageBox(("%s",nextVal));
//            lcd_->SetValue(nextVal);
//            lcd_->Update();
//            lcd_->Refresh();
//        }
//
//        wxQueueEvent(GetEventHandler(), new wxThreadEvent());
//    }
//    return (wxThread::ExitCode)0;
//}
//
//
//
//
//void SigrokLcdFrame::OnClose(wxCloseEvent&)
//{
//    // important: before terminating, we _must_ wait for our joinable
//    // thread to end, if it's running; in fact it uses variables of this
//    // instance and posts events to *this event handler
//    if (GetThread() &&      // DoStartALongTask() may have not been called
//        GetThread()->IsRunning())
//        GetThread()->Wait();
//    Destroy();
//}
//
//void SigrokLcdFrame::OnThreadUpdate(wxThreadEvent& evt)
//{
//    // ...do something... e.g. m_pGauge->Pulse();
//    // read some parts of m_data just for fun:
////    wxCriticalSectionLocker lock(m_dataCS);
////    wxPrintf("%c", m_data[100]);
//}

#endif // SIGROKLCDMAIN_H
