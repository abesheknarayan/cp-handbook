template <typename T>
struct point2d
{
  T x, y;
  point2d() : x(0), y(0) {}
  point2d(T _x, T _y) : x(_x), y(_y) {}

  point2d &operator+=(const point2d &p2)
  {
    x += p2.x;
    y += p2.y;
    return *this;
  }

  point2d &operator-=(const point2d &p2)
  {
    x -= p2.x;
    y -= p2.y;
    return *this;
  }

  point2d &operator*=(T t)
  {
    x *= t;
    y *= t;
    return *this;
  }

  point2d &operator/=(T t)
  {
    x /= t;
    y /= t;
    return *this;
  }

  point2d operator+(const point2d p2) const
  {
    return point2d(*this) += p2;
  }

  point2d operator-(const point2d p2) const
  {
    return point2d(*this) -= p2;
  }

  point2d operator*(T t) const
  {
    return point2d(*this) *= t;
  }

  point2d operator/(T t) const
  {
    return point2d(*this) /= t;
  }

  // dot product of 2 points
  friend T dot_product(point2d p1, point2d p2)
  {
    return p1.x * p2.x + p1.y * p2.y;
  }

  // square of point magnitude
  T norm(point2d p1)
  {
    return dot_product(p1, p1);
  }

  ld abs(point2d p1)
  {
    return sqrt(norm(p1));
  }

  // projection of p2 on p1 , |p2|cos(theta) =  (p1.p2) / |p1|
  ld proj(point2d p1, point2d p2)
  {
    return dot(p1, p2) / abs(p1);
  }

  // angle between 2 vectors
  ld angle(point2d p1, point2d p2)
  {
    return acos(dot(p1, p2) / (abs(p1) * abs(p2)));
  }

  friend T cross(point2d p1, point2d p2)
  {
    return p1.x * p2.y - p2.x * p1.y;
  }

  // finding cross product of p2,p3 wrt p1
  friend T cross3(point2d p1, point2d p2, point2d p3)
  {
    return cross(p2 - p1, p3 - p1);
  }

  point2d rotate90Anticlockwise()
  {
    return point2d(-y, x);
  }

  point2d rotate90Clockwise()
  {
    return point2d(y, -x);
  }

  // rotating with angle wrt center in anticlockwise direction
  point2d rotatePoint(point2d center, double angle)
  {
    point2d ref = (*this) - center;
    point2d ans;
    ans.x = ref.x * cos(angle) - ref.y * sin(angle);
    ans.y = ref.x * sin(angle) + ref.y * cos(angle);
    ans += center;
    return ans;
  }

  // iostreams
  friend std::istream &operator>>(std::istream &i, point2d &p)
  {
    return i >> p.x >> p.y;
  }

  friend std::ostream &operator>>(std::ostream &o, point2d &p)
  {
    return o << p.x << " " << p.y;
  }
};

template <typename T>
struct Line
{
  // starting point and the direction vector
  // any point on line is represented as st + k * dir
  point2d<T> st, dir;

  Line() : st(), dir() {}   
  Line(point2d<T> _st, point2d<T> _dir) : st(_st), dir(_dir) {}

  // construct a line segment using 2 points given
  friend Line constructLine(point2d<T> st, point2d<T> en)
  {
    point2d<T> dir = en - st;
    return Line(st, dir);
  }

  // finds if 2 line segments intersect
  friend bool LineSegmentsIntersect(const Line &l1, const Line &l2)
  {
  }
};