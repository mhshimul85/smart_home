var gulp = require('gulp'),
modernizr = require('gulp-modernizr');

/*
gulp.task('modernizr', function() {
  return gulp.src('./app/assets/scripts/* * / *.js')
    .pipe(modernizr({
      "options": [
        "setClasses"
      ]
    }))
    .pipe(gulp.dest('./app/temp/scripts/'));
});

*/

gulp.task('modernizr', function() {
  var settings = { 
    "options" : [
      "setClasses",
      "addTest",
      "html5printshiv",
      "testProp",
      "fnBind"
    ]
  };
  return gulp.src('./app/assets/scripts/* * / *.js')
    .pipe(modernizr(settings))
    .pipe(gulp.dest('./app/temp/scripts/')) // destination folder
});
