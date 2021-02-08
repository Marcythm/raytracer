use crate::utilities::*;
use crate::hittable::*;

#[derive(Debug, Clone, Copy, Default)]
pub struct Ray {
    origin: P3d,
    direction: Vec3,
}

impl Ray {
    pub fn new(origin: P3d, direction: Vec3) -> Self {
        Self { origin, direction }
    }
    pub fn between(origin: P3d, destination: P3d) -> Self {
        // generate a ray from origin to destination
        Self { origin, direction: destination - origin }
    }

    pub fn origin(&self) -> P3d {
        self.origin
    }
    pub fn direction(&self) -> Vec3 {
        self.direction
    }

    pub fn at(&self, t: f64) -> P3d {
        self.origin + t * self.direction
    }

    pub fn color<T: Hittable>(&self, world: &T, depth: i32, rng: &mut SmallRng) -> RGB {
        if depth <= 0 {
            return RGB::new(0.0, 0.0, 0.0);
        }
        if let Some(rec) = world.hit(&self, EPS, INFINITY) {
            0.5 * Ray::between(rec.p, rec.p + rec.normal + Vec3::random_unit_vector(rng)).color(world, depth - 1, rng)
        } else {
            let t = 0.5 * (self.direction.unit().y() + 1.0);
            (1.0 - t) * RGB::new(1.0, 1.0, 1.0) + t * RGB::new(0.5, 0.7, 1.0)
        }
    }
}
