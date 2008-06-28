// 
//   Copyright (C) 2005, 2006, 2007, 2008 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

#ifndef __PATH_PARSER_H
#define __PATH_PARSER_H


#include "shape.h"
#include <vector>
#include "cxform.h"

namespace gnash
{

/// Wraps a path, indicating whether we consider the left or the right of
/// the fill.
struct UnivocalPath
{
  enum fill_type
  {
    FILL_RIGHT,
    FILL_LEFT
  };
  
  UnivocalPath() : _path(NULL), _fill_type(FILL_LEFT) {}

  UnivocalPath(const path* path, fill_type filltype)
    : _path(path),
      _fill_type(filltype)
  {
  }
  
  const Point2d<int>& startPoint() const;
  const Point2d<int>& endPoint() const;

  const path* _path;
  fill_type   _fill_type;
};

/// PathParser is a class which aims to efficiently transpose Flash paths into
/// well formed, single-filled shapes.
//
/// A renderer should utilize this class by subclassing PathParser. The methods
/// reimplemented will receive low level path information (e.g., moveTo).
class PathParser : boost::noncopyable
{
public:
  /// @param paths list of Flash paths to be 'parsed'.
  /// @param num_styles count of fill styles pointed to by the first argument.
  PathParser(const std::vector<path>& paths, size_t num_styles);

  virtual ~PathParser() { }

  /// Runs the path parser, invoking the pure virtual methods where
  /// appropriate.
  /// @param cx the color transform that will be passed to prepareFill.
  /// @param mat the matrix that will be passed to prepareFill.
  void run(const cxform& cx, const matrix& mat);

  /// Prepare the fill style for subsequent use for filling one or more shapes.
  /// @param fill_style fill style number, as indicated by class Path.
  virtual void prepareFill(int fill_style, const cxform& cx, const matrix& mat) = 0;
  
  /// Terminates the fill style, that is, precludes the fill style from further
  /// use, which may be freed or otherwise cleaned up. Most renderers should
  /// fill the paths previously parsed.
  virtual void terminateFill(int fill_style) = 0;
  
  /// Fill a single shape. Implementation is optional, because most renderers
  /// can handle multiple well-formed, singly-filled shapes and can do the
  /// render/fill stage during terminateFill(). However, those that can't may
  /// implement this method.
  virtual void fillShape()
  {
  }
  
  /// Move the path pencil to the given location. Thus a new shape should be
  /// started. The parser may invoke this method several times for a single
  /// fill style, creating several shapes.
  virtual void moveTo(const geometry::Point2d<int>& p) = 0;
  
  /// Draw the given curve using the path pencil.
  virtual void curveTo(const Edge<int>& curve) = 0;

  /// Draw a straight line to the given point.
  virtual void lineTo(const geometry::Point2d<int>& p) = 0;

private:
  bool emitConnecting(const UnivocalPath& subject);
    
  void append(const UnivocalPath& append_path);
  
  void start_shapes(int fill_style, const cxform& cx, const matrix& mat);

  void end_shapes(int fill_style);

  void reset_shape(const UnivocalPath& append_path);
  
  bool closed_shape();


  const std::vector<path>& _paths;
  const size_t             _num_styles;
  Point2d<int>       _shape_origin;
  Point2d<int>       _cur_endpoint;
};

}

#endif // __PATH_PARSER_H
