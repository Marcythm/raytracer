use crate::utilities::prelude::*;
use crate::hittable::prelude::*;
use crate::pdf::{
    prelude::*,
    cosine_pdf::CosinePDF,
    hittable_pdf::HittablePDF,
    mixture_pdf::MixturePDF,
};

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

    pub fn color<T: Hittable>(&self, world: &T, background: RGB, lights: Rc<dyn Hittable>, depth: i32, rng: &mut SmallRng) -> RGB {
        if depth <= 0 {
            RGB::new(0.0, 0.0, 0.0)
        } else if let Some(rec) = world.hit(&self, EPS, INFINITY) {
            let emitted = rec.material.emitted(rec.u, rec.v, rec.p);
            if let Some((_, attenuation, _)) = rec.material.scatter(self, &rec, rng) {
                let pdf0 = CosinePDF::new(rec.normal);
                let pdf1 = HittablePDF::new(lights.clone(), rec.p);
                let pdf = MixturePDF::new(Rc::new(pdf0), Rc::new(pdf1));

                let scattered = Ray::new(rec.p, pdf.generate(rng), self.time);
                let pdf_val = pdf.value(scattered.direction);

                emitted + attenuation
                * rec.material.scattering_pdf(self, &rec, &scattered)
                * scattered.color(world, background, lights, depth - 1, rng)
                / pdf_val
            } else {
                emitted
            }
        } else {
            background
        }
    }
}
