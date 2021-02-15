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
            let emitted = rec.material.emitted(rec.u, rec.v, rec.p);
            if let Some((_, attenuation, _)) = rec.material.scatter(self, &rec, rng) {
                let on_light = P3d::new(rng.gen_range(213.0, 343.0), 554.0, rng.gen_range(227.0, 332.0));
                let to_light = on_light - rec.p;
                let distance_squared = to_light.length2();
                let to_light = to_light.unit();

                if to_light.dot(rec.normal) < 0.0 {
                    emitted
                } else {
                    let light_area = (343.0 - 213.0) * (332.0 - 227.0);
                    let light_cosine = to_light.y.abs();

                    if light_cosine < EPS {
                        emitted
                    } else {
                        let pdf_val = distance_squared / (light_cosine * light_area);
                        let scattered = Ray::new(rec.p, to_light, self.time);

                        emitted + attenuation
                      * rec.material.scattering_pdf(self, &rec, &scattered)
                      * scattered.color(world, background, depth - 1, rng)
                      / pdf_val
                    }
                }
            } else {
                emitted
            }
        } else {
            background
        }
    }
}
