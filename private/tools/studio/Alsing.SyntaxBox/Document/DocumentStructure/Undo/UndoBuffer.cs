// *
// * Copyright (C) 2008 Roger Studio.Alsing : http://www.RogerAlsing.com
// *
// * This library is free software; you can redistribute it and/or modify it
// * under the terms of the GNU Lesser General Public License 2.1 or later, as
// * published by the Free Software Foundation. See the included license.txt
// * or http://www.gnu.org/copyleft/lesser.html for details.
// *
// *

using System.Collections.Generic;

namespace Studio.Alsing.SourceCode
{
    /// <summary>
    /// 
    /// </summary>
    public sealed class UndoBuffer : List<UndoBlockCollection>
    {
        public UndoBuffer()
        {
            MaxSize = 1000;
        }

        public int MaxSize { get; set; }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="index"></param>
        public void ClearFrom(int index)
        {
            while (index <= Count - 1)
                RemoveAt(index);
        }
    }
}