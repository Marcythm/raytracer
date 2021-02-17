use super::{
    utilities::prelude::*,
    hittable::prelude::*,
    material::prelude::*,
    pdf::{
        prelude::*,
        // cosine_pdf::CosinePDF,
        hittable_pdf::HittablePDF,
        mixture_pdf::MixturePDF,
    },
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

    pub fn color(&self, world: Rc<dyn Hittable>, background: RGB, lights: Rc<dyn Hittable>, depth: u32, rng: &mut SmallRng) -> RGB {
        if depth <= 0 {
            RGB::new(0.0, 0.0, 0.0)
        } else if let Some(hit_rec) = world.hit(&self, EPS, INFINITY) {
            let emitted = hit_rec.material.emitted(self, &hit_rec, hit_rec.u, hit_rec.v, hit_rec.p);
            if let Some(scatter_rec) = hit_rec.material.scatter(self, &hit_rec, rng) {
                match scatter_rec {
                    ScatterRecord::Specular {
                        specular_ray,
                        attenuation,
                    } => {
                        attenuation * specular_ray.color(world, background, lights, depth - 1, rng)
                    },
                    ScatterRecord::Diffuse {
                        pdf,
                        attenuation,
                    } => {
                        let light_pdf = HittablePDF::new(lights.clone(), hit_rec.p);
                        let pdf = MixturePDF::new(pdf, Rc::new(light_pdf));

                        let scattered = Ray::new(hit_rec.p, pdf.generate(rng), self.time);
                        let pdf_val = pdf.value(scattered.direction);

                        emitted + attenuation
                        * hit_rec.material.scattering_pdf(self, &hit_rec, &scattered)
                        * scattered.color(world, background, lights, depth - 1, rng)
                        / pdf_val
                    },
                }

            } else {
                emitted
            }
        } else {
            background
        }
    }
}
