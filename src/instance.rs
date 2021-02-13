use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::aabb::AABB;
use crate::hittable::prelude::*;
use crate::transform::prelude::*;

/// Apply a transform to a hittable object
#[derive(Clone)]
pub struct Instance {
    pub hittable  : Rc<dyn Hittable>,
    pub transform : Rc<dyn Transform>,
}

impl Instance {
    pub fn new(hittable: Rc<dyn Hittable>, transform: Rc<dyn Transform>) -> Self {
        Self { hittable, transform }
    }
}

impl Hittable for Instance {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        let inverse_transformed_ray = self.transform.inverse_transform_ray(ray);
        if let Some(mut rec) = self.hittable.hit(&inverse_transformed_ray, t_min, t_max) {
            rec.p      = self.transform.transform_point(rec.p);
            rec.normal = self.transform.transform_vector(rec.normal);
            rec.set_face_normal(&inverse_transformed_ray);
            Some(rec)
        } else {
            None
        }
    }

    fn bounding_box(&self, t0: f64, t1: f64) -> Option<AABB> {
        if let Some(bounding_box) = self.hittable.bounding_box(t0, t1) {
            Some(self.transform.transform_box(&bounding_box))
        } else {
            None
        }
    }
}

impl Transform for Instance {
    fn transform_point(&self, p: P3d) -> P3d {
        self.transform.transform_point(p)
    }

    fn inverse_transform_point(&self, p: P3d) -> P3d {
        self.transform.inverse_transform_point(p)
    }

    fn transform_vector(&self, v: Vec3) -> Vec3 {
        self.transform.transform_vector(v)
    }

    fn inverse_transform_vector(&self, v: Vec3) -> Vec3 {
        self.transform.inverse_transform_vector(v)
    }

    fn transform_ray(&self, ray: &Ray) -> Ray {
        self.transform.transform_ray(ray)
    }

    fn inverse_transform_ray(&self, ray: &Ray) -> Ray {
        self.transform.inverse_transform_ray(ray)
    }

    fn transform_box(&self, bounding_box: &AABB) -> AABB {
        self.transform.transform_box(bounding_box)
    }

    fn inverse_transform_box(&self, bounding_box: &AABB) -> AABB {
        self.transform.inverse_transform_box(bounding_box)
    }
}
