use super::super::{
    utilities::prelude::*,
    ray::Ray,
    aabb::AABB,
    hittable::{
        prelude::*,
        aarectangle::{
            XYAARectangle,
            YZAARectangle,
            ZXAARectangle,
        },
    },
    material::prelude::*,
};

#[derive(Clone)]
pub struct Cuboid {
    pub min      : P3d,
    pub max      : P3d,
    pub surfaces : HittableList,
}

impl Cuboid {
    pub fn new(min: P3d, max: P3d, material: Rc<dyn Material>) -> Self {
        let mut surfaces = HittableList::default();

        surfaces.push(XYAARectangle::new(min.x, max.x, min.y, max.y, min.z, material.clone()));
        surfaces.push(XYAARectangle::new(min.x, max.x, min.y, max.y, max.z, material.clone()));

        surfaces.push(YZAARectangle::new(min.y, max.y, min.z, max.z, min.x, material.clone()));
        surfaces.push(YZAARectangle::new(min.y, max.y, min.z, max.z, max.x, material.clone()));

        surfaces.push(ZXAARectangle::new(min.z, max.z, min.x, max.x, min.y, material.clone()));
        surfaces.push(ZXAARectangle::new(min.z, max.z, min.x, max.x, max.y, material.clone()));

        Self {
            min,
            max,
            surfaces,
        }
    }
}

impl Hittable for Cuboid {
    fn hit(&self, ray: &Ray, t_min: f64, t_max: f64) -> Option<HitRecord> {
        self.surfaces.hit(ray, t_min, t_max)
    }

    fn bounding_box(&self, _: f64, _: f64) -> Option<AABB> {
        Some(AABB::new(self.min, self.max))
    }
}
