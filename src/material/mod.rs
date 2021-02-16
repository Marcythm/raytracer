pub mod lambertian;
pub mod metal;
pub mod dielectric;
pub mod diffuse_light;
pub mod isotropic;

pub mod prelude {
    pub use super::{
        ScatterRecord,
        Material,
    };
}

use super::{
    utilities::prelude::*,
    ray::Ray,
    hittable::prelude::*,
    pdf::prelude::*,
};

#[derive(Clone)]
pub enum ScatterRecord {
    Specular {
        specular_ray: Ray,
        attenuation: RGB,
    },
    Diffuse {
        pdf: Rc<dyn PDF>,
        attenuation: RGB,
    }
}

pub trait Material {
    #[allow(unused_variables)]
    fn emitted(&self, ray: &Ray, rec: &HitRecord, u: f64, v: f64, p: P3d) -> RGB {
        RGB::new(0.0, 0.0, 0.0)
    }

    #[allow(unused_variables)]
    fn scatter(&self, ray: &Ray, rec: &HitRecord, rng: &mut SmallRng) -> Option<ScatterRecord> {
        None
    }

    #[allow(unused_variables)]
    fn scattering_pdf(&self, ray: &Ray, rec: &HitRecord, scattered: &Ray) -> f64 {
        0.0
    }
}
