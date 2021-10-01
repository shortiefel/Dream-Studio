using System.Runtime.CompilerServices; //For internal calls

public class SceneManager
{
    public static void LoadScene(string sceneName)
    {
        LoadScene_Engine(sceneName);
    }
    [MethodImpl(MethodImplOptions.InternalCall)]
    internal static extern void LoadScene_Engine(string sceneName);
}
