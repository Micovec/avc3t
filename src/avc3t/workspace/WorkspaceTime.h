#pragma once

namespace AVC3T {
    class WorkspaceTime {
      public:
        WorkspaceTime() : m_Running(true), m_WaitingResetForResume(false), m_Time(0), m_LastTime(0), m_ResumeTimeDelta(0) {}

        void Resume() {
            if (m_Running)
                return;

            m_Running = true;
            if (m_WaitingResetForResume) {
                m_WaitingResetForResume = false;
                m_ResumeTimeDelta       = m_LastTime;
                return;
            }

            m_ResumeTimeDelta = m_LastTime - m_Time;
        }

        void Pause() {
            m_Running = false;
        }

        void Reset() {
            m_ResumeTimeDelta = m_LastTime;
            if (!m_Running) {
                m_WaitingResetForResume = true;
                m_Time                  = 0;
            }
        }

        void Update(double ts) {
            m_LastTime = ts;

            if (!m_Running)
                return;

            m_Time = ts - m_ResumeTimeDelta;
        }

        double GetTime() const {
            return m_Time;
        }

      private:
        bool   m_Running, m_WaitingResetForResume;
        double m_Time, m_LastTime, m_ResumeTimeDelta;
    };
}