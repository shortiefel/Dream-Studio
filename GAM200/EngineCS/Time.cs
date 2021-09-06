using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices; //For internal calls

public  class Time
{
    public static float dt
    {
        get
        {
            GetDeltaTime_Engine(out float result);
            return result;
        }
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void GetDeltaTime_Engine(out float outFloat);
}
