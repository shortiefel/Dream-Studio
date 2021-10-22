/* Start Header**********************************************************************************/
/*
@file    CommandHistory.hpp
@author  Goh See Yong, Denise  	g.seeyongdenise@digipen.edu
@date    21/10/2021
\brief
This file contain the Command declaration regarding Undo / Redo.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/pch.hpp"

namespace Engine {

    class ICommand {
    public:
        virtual ~ICommand() {}
        virtual void execute() = 0;
        virtual void undo() = 0;
        virtual bool mergeWith(ICommand* other) = 0;

        void SetNoMerge() { m_CanMerge = false; }
        bool CanMerge() const { return m_CanMerge; }

    private:
        static GLuint64 m_Id;

    protected:
        bool m_CanMerge = true;
    };

    class CommandHistory {
    public:
        static void AddCommand(ICommand* cmd);
        static void SetNoMergeMostRecent();
        static void Undo();
        static void Redo();

    private:
        static ICommand* m_Commands[1000];
        static int m_CommandSize;
        static int m_CommandPtr;
    };
}
