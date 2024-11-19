#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Classe de base Point
class Point {
protected:
    vector<float> coordinates;

public:
    // Constructeur générique pour un point avec n dimensions
    Point(initializer_list<float> coords) : coordinates(coords) {}

    // Méthode pour calculer la distance entre deux points
    float distance(const Point& p) const {
        float sum = 0;
        for (size_t i = 0; i < coordinates.size(); ++i) {
            sum += pow(coordinates[i] - p.coordinates[i], 2);
        }
        return sqrt(sum);
    }

    // Méthode pour transformer un point 3D en 2D
    Point* transformerEn2D() {
        if (coordinates.size() == 3) {
            return new Point2D(coordinates[0], coordinates[1]);
        }
        return this; // Retourner le même point si déjà 2D
    }

    // Méthode pour transformer un point 2D en 3D
    Point* transformerEn3D() {
        if (coordinates.size() == 2) {
            return new Point3D(coordinates[0], coordinates[1], 0);
        }
        return this; // Retourner le même point si déjà 3D
    }
};

// Classe Point2D héritant de Point
class Point2D : public Point {
public:
    Point2D(float x, float y) : Point({x, y}) {}

    // Méthode pour calculer la distance entre deux points 2D
    float distance(const Point2D& p) const {
        return Point::distance(p);
    }
};

// Classe Point3D héritant de Point
class Point3D : public Point {
public:
    Point3D(float x, float y, float z) : Point({x, y, z}) {}

    // Méthode pour calculer la distance entre deux points 3D
    float distance(const Point3D& p) const {
        return Point::distance(p);
    }
};

// Classe Parcours (générique pour les parcours de points)
class Parcours {
protected:
    vector<Point*> points;

public:
    // Méthode pour ajouter un point au parcours
    void ajouterPoint(Point* p) {
        points.push_back(p);
    }

    // Méthode pour calculer la distance totale du parcours
    float calculerDistance() const {
        float totalDistance = 0.0;
        for (size_t i = 1; i < points.size(); ++i) {
            totalDistance += points[i - 1]->distance(*points[i]);
        }
        return totalDistance;
    }
};

// Classe Parcours2D héritant de Parcours
class Parcours2D : public Parcours {
public:
    void ajouterPoint(Point2D* p) {
        Parcours::ajouterPoint(p);
    }
};

// Classe Parcours3D héritant de Parcours
class Parcours3D : public Parcours {
public:
    void ajouterPoint(Point3D* p) {
        Parcours::ajouterPoint(p);
    }
};

int main() {
    // Création de points 2D et 3D
    Point2D* point2d_1 = new Point2D(1, 2);
    Point2D* point2d_2 = new Point2D(3, 4);
    Point3D* point3d_1 = new Point3D(1, 2, 3);
    Point3D* point3d_2 = new Point3D(4, 5, 6);

    // Création de parcours
    Parcours2D parcours2D;
    Parcours3D parcours3D;

    // Ajout de points aux parcours
    parcours2D.ajouterPoint(point2d_1);
    parcours2D.ajouterPoint(point2d_2);

    parcours3D.ajouterPoint(point3d_1);
    parcours3D.ajouterPoint(point3d_2);

    // Calcul de la distance totale pour chaque parcours
    cout << "Distance totale parcours 2D: " << parcours2D.calculerDistance() << endl;
    cout << "Distance totale parcours 3D: " << parcours3D.calculerDistance() << endl;

    // Transformation d'un point 3D en 2D
    Point* transformedPoint = point3d_1->transformerEn2D();
    cout << "Transformation du point 3D en 2D : distance entre points transformés : "
         << point2d_1->distance(*dynamic_cast<Point2D*>(transformedPoint)) << endl;

    // Libération de la mémoire
    delete point2d_1;
    delete point2d_2;
    delete point3d_1;
    delete point3d_2;

    return 0;
}
