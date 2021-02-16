use super::super::{
    utilities::prelude::*,
    ray::Ray,
    aabb::AABB,
    transform::prelude::*,
};

#[derive(Clone)]
pub struct Flip {

}

impl Flip {
    pub fn new() -> Self {
        Self { }
    }
}

impl Transform for Flip {
    fn transform_vector(&self, v: Vec3) -> Vec3 {
        -v
    }

    fn inverse_transform_vector(&self, v: Vec3) -> Vec3 {
        -v
    }

    fn transform_ray(&self, ray: &Ray) -> Ray {
        ray.clone()
    }

    fn inverse_transform_ray(&self, ray: &Ray) -> Ray {
        ray.clone()
    }

    fn transform_box(&self, bounding_box: &AABB) -> AABB {
        bounding_box.clone()
    }

    fn inverse_transform_box(&self, bounding_box: &AABB) -> AABB {
        bounding_box.clone()
    }
}
