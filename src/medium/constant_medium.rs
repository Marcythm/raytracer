use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::aabb::AABB;
use crate::hittable::prelude::*;
use crate::material::prelude::*;
use crate::material::isotropic::Isotropic;
use crate::texture::prelude::*;
use crate::medium::prelude::*;

#[derive(Clone)]
pub struct ConstantMedium {
    pub boundary: Rc<dyn Hittable>,
    pub material: Rc<dyn Material>,
    pub negative_inverse_density: f64,
    pub rng: RefCell<SmallRng>,
}

impl ConstantMedium {
    pub fn new(boundary: Rc<dyn Hittable>, texture: Rc<dyn Texture>, density: f64) -> Self {
        Self {
            boundary,
            material: Rc::new(Isotropic::with_texture(texture)),
            negative_inverse_density: -1.0 / density,
            rng: RefCell::new(SmallRng::from_entropy()),
        }
    }

    pub fn with_color(boundary: Rc<dyn Hittable>, color: RGB, density: f64) -> Self {
        Self {
            boundary,
            material: Rc::new(Isotropic::with_color(color)),
            negative_inverse_density: -1.0 / density,
            rng: RefCell::new(SmallRng::from_entropy()),
        }
    }
}

impl Hittable for ConstantMedium {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        if let Some(mut rec_in) = self.boundary.hit(ray, -INFINITY, INFINITY) {
            if let Some(mut rec_out) = self.boundary.hit(ray, rec_in.t + EPS, INFINITY) {
                if rec_in.t  < t_min { rec_in.t  = t_min; }
                if rec_out.t > t_max { rec_out.t = t_max; }
                if rec_in.t < rec_out.t {
                    if rec_in.t < 0.0 { rec_in.t = 0.0; }

                    let mut rng = self.rng.borrow_mut();

                    let ray_length = ray.direction.length();
                    let distance_in_medium = (rec_out.t - rec_in.t) * ray_length;
                    let hit_distance = self.negative_inverse_density * ((rng.gen_range(0.0, 1.0) as f64).log10());

                    if hit_distance > distance_in_medium {
                        None
                    } else {
                        let hit_time = rec_in.t + hit_distance / ray_length;
                        Some(HitRecord::new(
                            ray.at(hit_time),
                            Vec3::random_unit_vector(&mut rng),
                            hit_time,
                            rng.gen_range(0.0, 1.0),
                            rng.gen_range(0.0, 1.0),
                            self.material.clone(),
                            ray,
                        ))
                    }
                } else {
                    None
                }
            } else {
                None
            }
        } else {
            None
        }
    }

    fn bounding_box(&self, t0: f64, t1: f64) -> Option<AABB> {
        self.boundary.bounding_box(t0, t1)
    }
}

impl Medium for ConstantMedium {

}
