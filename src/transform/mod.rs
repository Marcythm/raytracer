pub mod prelude {
    pub use super::Transform;
}

use crate::utilities::prelude::*;
use crate::ray::Ray;
use crate::aabb::AABB;

pub trait Transform {
    fn transform_point(&self, p: P3d) -> P3d;
    fn inverse_transform_point(&self, p: P3d) -> P3d;

    fn transform_vector(&self, v: Vec3) -> Vec3;
    fn inverse_transform_vector(&self, v: Vec3) -> Vec3;

    fn transform_ray(&self, ray: Ray) -> Ray {
        Ray::new(
            self.transform_point(ray.origin),
            self.transform_vector(ray.direction),
            ray.time,
        )
    }
    fn inverse_transform_ray(&self, ray: Ray) -> Ray {
        Ray::new(
            self.inverse_transform_point(ray.origin),
            self.inverse_transform_vector(ray.direction),
            ray.time,
        )
    }

    fn transform_box(&self, bounding_box: AABB) -> AABB {
        let mut min = P3d::new(-INFINITY, -INFINITY, -INFINITY);
        let mut max = P3d::new( INFINITY,  INFINITY,  INFINITY);

        for i in 0..2 {
            for j in 0..2 {
                for k in 0..2 {
                    let transformed_p = self.transform_point(
                        P3d::new(bounding_box[i].x, bounding_box[j].y, bounding_box[k].z)
                    );

                    for axis in 0..3 {
                        if min[axis] > transformed_p[axis] {
                            min[axis] = transformed_p[axis];
                        }
                        if max[axis] < transformed_p[axis] {
                            max[axis] = transformed_p[axis];
                        }
                    }
                }
            }
        }

        AABB::new(min, max)
    }
    fn inverse_transform_box(&self, bounding_box: AABB) -> AABB {
        let mut min = P3d::new(-INFINITY, -INFINITY, -INFINITY);
        let mut max = P3d::new( INFINITY,  INFINITY,  INFINITY);

        for i in 0..2 {
            for j in 0..2 {
                for k in 0..2 {
                    let inverse_transformed_p = self.inverse_transform_point(
                        P3d::new(bounding_box[i].x, bounding_box[j].y, bounding_box[k].z)
                    );

                    for axis in 0..3 {
                        if min[axis] > inverse_transformed_p[axis] {
                            min[axis] = inverse_transformed_p[axis];
                        }
                        if max[axis] < inverse_transformed_p[axis] {
                            max[axis] = inverse_transformed_p[axis];
                        }
                    }
                }
            }
        }

        AABB::new(min, max)
    }
}
