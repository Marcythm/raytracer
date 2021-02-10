use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::hittable::prelude::*;

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
            let t0 = (self.min[axis] - ray.origin[axis]) / ray.direction[axis];
            let t1 = (self.max[axis] - ray.origin[axis]) / ray.direction[axis];
            tmin = tmin.max(t0.min(t1));
            tmax = tmax.min(t0.max(t1));
            if tmax <= tmin {
                return false;
            }
        }
        true
    }
}
