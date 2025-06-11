#pragma once

class Vec {
 public:
  Vec();

  Vec(float x, float y);

  Vec operator+(Vec const& rhs);

  Vec& operator+=(Vec const& rhs);

  Vec operator*(float rhs);

  float x, y;
};
