use std::ops::{Index, IndexMut};

use crate::utilities::prelude::*;
use crate::ray::Ray;

#[derive(Debug, Clone, Copy, Default)]
pub struct AABB { // Axis-Aligned Bounding Box
    pub min: P3d,
    pub max: P3d,
}

impl AABB {
    pub fn new(min: P3d, max: P3d) -> Self {
        Self { min, max }
    }

    pub fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> bool {
        let mut tmin = t_min;
        let mut tmax = t_max;
        for axis in 0..3 {
            let inv_d = 1.0 / ray.direction[axis];
            let mut t0 = (self.min[axis] - ray.origin[axis]) * inv_d;
            let mut t1 = (self.max[axis] - ray.origin[axis]) * inv_d;
            if inv_d < 0.0 {
                std::mem::swap(&mut t0, &mut t1);
            }
            if t0 > tmin { tmin = t0; }
            if t1 < tmax { tmax = t1; }
            if tmax <= tmin {
                return false;
            }
        } true
    }

    pub fn surrounding_box(box0: &Self, box1: &Self) -> Self {
        Self {
            min: P3d::new(
                box0.min.x.min(box1.min.x),
                box0.min.y.min(box1.min.y),
                box0.min.z.min(box1.min.z),
            ),
            max: P3d::new(
                box0.max.x.max(box1.max.x),
                box0.max.y.max(box1.max.y),
                box0.max.z.max(box1.max.z),
            ),
        }
    }
}

impl Index<i32> for AABB {
    type Output = P3d;
    fn index(&self, index: i32) -> &Self::Output {
        if index == 0 { &self.min } else { &self.max }
    }
}

impl IndexMut<i32> for AABB {
    fn index_mut(&mut self, index: i32) -> &mut Self::Output {
        if index == 0 { &mut self.min } else { &mut self.max }
    }
}
