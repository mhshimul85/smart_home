var gulp = require('gulp');
var sass = require('gulp-sass');
var postcss = require('gulp-postcss');
var autoprefixer = require('autoprefixer');
 
sass.compiler = require('node-sass');

gulp.task('styles', function() {
  return gulp.src('./app/assets/styles/styles.scss')
    .pipe(sass.sync().on('error', sass.logError))
    .pipe(postcss([autoprefixer]))
      .on('error', function(errorInfo) {
        console.log(errorInfo.toString());
        this.emit('end');
        })
    .pipe(gulp.dest('./app/temp/styles'));
});