//
// LICENCE:
//  The MIT License (MIT)
//
//  Copyright (c) 2016 Karim Naaji, karim.naaji@gmail.com
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE
//
// REFERENCES:
//  [1] http://box2d.org/files/GDC2014/DirkGregorius_ImplementingQuickHull.pdf
//  [2] http://www.cs.smith.edu/~orourke/books/compgeom.html
//  [3] http://www.flipcode.com/archives/The_Half-Edge_Data_Structure.shtml
//  [4] http://doc.cgal.org/latest/HalfedgeDS/index.html
//  [5] http://thomasdiewald.com/blog/?p=1888
//  [6] https://fgiesen.wordpress.com/2012/02/21/half-edge-based-mesh-representations-theory/
//
// HOWTO:
//  #define QUICKHULL_IMPLEMENTATION
//  #define QUICKHULL_DEBUG // Only if assertions need to be checked
//  #include "quickhull.h"
//
// HISTORY:
//  - 1.0.1 (2016-11-01): Various improvements over epsilon issues and degenerate faces
//                        Debug functionalities to test final results dynamically
//                        API to export hull meshes in OBJ files
//  - 1.0   (2016-09-10): Initial
//
// TODO:
//  - use float* from public interface
//  - reduce memory usage

#ifndef QUICKHULL_H
#define QUICKHULL_H

// ------------------------------------------------------------------------------------------------
// QUICKHULL PUBLIC API
//

typedef struct qh_vertex {
    union {
        float v[3];
        struct {
            float x;
            float y;
            float z;
        };
    };
} qh_vertex_t;

typedef qh_vertex_t qh_vec3_t;

typedef struct qh_mesh {
    qh_vertex_t* vertices;
    qh_vec3_t* normals;
    unsigned int* indices;
    unsigned int* normalindices;
    unsigned int nindices;
    unsigned int nvertices;
    unsigned int nnormals;
} qh_mesh_t;

qh_mesh_t qh_quickhull3d(qh_vertex_t const* vertices, unsigned int nvertices);

void qh_mesh_export(qh_mesh_t const* mesh, char const* filename);

void qh_free_mesh(qh_mesh_t mesh);

//
// END QUICKHULL PUBLIC API
// ------------------------------------------------------------------------------------------------

#endif // QUICKHULL_H
