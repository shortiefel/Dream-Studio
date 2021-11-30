
public class GameState : MonoBehaviour
{
    bool pauseState;
    bool drawModeBool;

    public void InvertPause()
    {
        pauseState = !pauseState;
    }
    public bool GetPause()
    {
        return pauseState;
    }

    public void SetDrawMode(bool _state)
    {
        drawModeBool = _state;
    }
    public bool GetDrawMode()
    {
        return drawModeBool;
    }

    public bool ShouldDraw()
    {
        return !pauseState && drawModeBool;
    }

    public override void Start()
    {
        pauseState = false;
        drawModeBool = false;
    }
}