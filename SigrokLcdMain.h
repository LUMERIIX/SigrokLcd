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

//(*Headers(LcdTestFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
//*)

class SigrokLcdFrame: public wxFrame
{
    public:

       SigrokLcdFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~SigrokLcdFrame();

        //wxListBox *listbox1;

    private:
        wxLCDWindow *lcd_;
        awxLed *ledmHz_;
        awxLed *ledHz_;
        awxLed *ledkHz_;
        awxLed *ledMHz_;
        uint8_t ledState_;

        std::shared_ptr<sigrok::Context> context_;
        std::shared_ptr<sigrok::Session> session_;
        void sigrok_datafeed_callback(std::shared_ptr<sigrok::Device> hwDev, std::shared_ptr<sigrok::Packet> packet);
        void sigrok_stopped_callback();




        //(*Handlers(LcdTestFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnConnect(wxCommandEvent& event);
        void OnDisconnect(wxCommandEvent& event);
        //*)

        //(*Identifiers(LcdTestFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long idMenuConnect;
        static const long idMenuDisconnect;

        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(LcdTestFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SIGROKLCDMAIN_H
