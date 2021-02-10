use crate::utilities::prelude::*;
use crate::hittable::prelude::*;

#[derive(Clone)]
pub struct Ray {
    pub origin    : P3d,
    pub direction : Vec3,
    pub time      : f64,
}

impl Ray {
    pub fn new(origin: P3d, direction: Vec3, time: f64) -> Self {
        Self { origin, direction, time }
    }
    pub fn from_to(from: P3d, to: P3d, time: f64) -> Self {
        // generate a ray from origin to destination
        Self { origin: from, direction: to - from, time }
    }

    pub fn at(&self, t: f64) -> P3d {
        self.origin + t * self.direction
    }

    pub fn color<T: Hittable>(&self, world: &T, background: RGB, depth: i32, rng: &mut SmallRng) -> RGB {
        if depth <= 0 {
            return RGB::new(0.0, 0.0, 0.0);
        }
        if let Some(rec) = world.hit(&self, EPS, INFINITY) {
            rec.material.emitted(rec.u, rec.v, rec.p) +
            if let Some((scattered, attenuation)) = rec.material.scatter(self, &rec, rng) {
                attenuation * scattered.color(world, background, depth - 1, rng)
            } else {
                RGB::new(0.0, 0.0, 0.0)
            }
        } else {
            background
        }
    }
}
