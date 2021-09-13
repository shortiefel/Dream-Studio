using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices; //For internal calls

public class Input
{
    public static bool IsKeyPressed(KeyCode keyCode)
    {
        return IsKeyPressed_Engine(keyCode);
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool IsKeyPressed_Engine(KeyCode key);

    public static bool IsMousePressed(MouseCode button)
    {
        return IsMousePressed_Engine(button);
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool IsMousePressed_Engine(MouseCode button);

    public static Vec2 GetMousePosition_Engine()
    {
        GetMousePosition_Engine(out Vec2 position);
        return position;
    }

    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern bool GetMousePosition_Engine(out Vec2 pos);

}
