using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSFormSerp
{
    interface IDrawableArea
    {
        void drawEllipse(System.Drawing.Color color, float centerX, float centerY, float width, float height);

        void drawRectangle(System.Drawing.Color color, float left, float top, float width, float height);

        void drawLine(System.Drawing.Color color, float fromX, float fromY, float toX, float toY);

        void drawText(string text, System.Drawing.Color color, float fromX, float fromY);

        void newFrame();

        void drawOnGraphics(System.Drawing.Graphics target);
    }
}
