#pragma once
#include <concepts>
#include <functional>

namespace mgo
{
enum struct _matrix_space
{
  TRANSPOSE,
  COLUMN,
  ROW
};

template <class matrix_type, _matrix_space space>
struct _matrix_view_data;

template <class underling_matrix_type>
struct _matrix_view_data<underling_matrix_type, _matrix_space::TRANSPOSE>
{
  protected:
    using size_type                        = typename underling_matrix_type::size_type;
    using difference_type                  = typename underling_matrix_type::difference_type;
    using value_type                       = typename underling_matrix_type::value_type;
    using reference                        = typename underling_matrix_type::reference;
    using const_reference                  = typename underling_matrix_type::const_reference;
    using pointer                          = typename underling_matrix_type::pointer;
    using const_pointer                    = typename underling_matrix_type::const_pointer;
    using matrix_type                      = typename underling_matrix_type::transpose_type;
    using matrix_view                      = typename underling_matrix_type::transpose_view;
    using const_matrix_view                = typename underling_matrix_type::const_transpose_view;
    using iterator                         = typename underling_matrix_type::transpose_iterator;
    using const_iterator                   = typename underling_matrix_type::const_transpose_iterator;
    using reverse_iterator                 = typename underling_matrix_type::reverse_transpose_iterator;
    using const_reverse_iterator           = typename underling_matrix_type::const_reverse_transpose_iterator;
    using transpose_type                   = typename underling_matrix_type::matrix_type;
    using transpose_view                   = typename underling_matrix_type::matrix_view;
    using const_transpose_view             = typename underling_matrix_type::const_matrix_view;
    using transpose_iterator               = typename underling_matrix_type::matrix_iterator;
    using const_transpose_iterator         = typename underling_matrix_type::const_matrix_iterator;
    using reverse_transpose_iterator       = typename underling_matrix_type::reverse_matrix_iterator;
    using const_reverse_transpose_iterator = typename underling_matrix_type::const_reverse_matrix_iterator;
    using column_type                      = typename underling_matrix_type::row_type;
    using column_view                      = typename underling_matrix_type::row_view;
    using const_column_view                = typename underling_matrix_type::const_row_view;
    using column_iterator                  = typename underling_matrix_type::row_iterator;
    using const_column_iterator            = typename underling_matrix_type::const_row_iterator;
    using reverse_column_iterator          = typename underling_matrix_type::reverse_row_iterator;
    using const_reverse_column_iterator    = typename underling_matrix_type::const_reverse_row_iterator;
    using row_type                         = typename underling_matrix_type::column_type;
    using row_view                         = typename underling_matrix_type::column_view;
    using const_row_view                   = typename underling_matrix_type::const_column_view;
    using row_iterator                     = typename underling_matrix_type::column_iterator;
    using const_row_iterator               = typename underling_matrix_type::const_column_iterator;
    using reverse_row_iterator             = typename underling_matrix_type::reverse_column_iterator;
    using const_reverse_row_iterator       = typename underling_matrix_type::const_reverse_column_iterator;
    using diagonal_iterator                = typename underling_matrix_type::diagonal_iterator;
    using const_diagonal_iterator          = typename underling_matrix_type::const_diagonal_iterator;
    using reverse_diagonal_iterator        = typename underling_matrix_type::reverse_diagonal_iterator;
    using const_reverse_diagonal_iterator  = typename underling_matrix_type::const_reverse_diagonal_iterator;

    std::reference_wrapper<underling_matrix_type> _base;
};

template <class underling_matrix_type>
struct _matrix_view_data<underling_matrix_type, _matrix_space::COLUMN>
{
  protected:
    using size_type                        = typename underling_matrix_type::size_type;
    using difference_type                  = typename underling_matrix_type::difference_type;
    using value_type                       = typename underling_matrix_type::value_type;
    using reference                        = typename underling_matrix_type::reference;
    using const_reference                  = typename underling_matrix_type::const_reference;
    using pointer                          = typename underling_matrix_type::pointer;
    using const_pointer                    = typename underling_matrix_type::const_pointer;
    using matrix_type                      = typename underling_matrix_type::column_type;
    using matrix_view                      = typename underling_matrix_type::column_view;
    using const_matrix_view                = typename underling_matrix_type::const_column_view;
    using iterator                         = typename underling_matrix_type::column_iterator;
    using const_iterator                   = typename underling_matrix_type::const_column_iterator;
    using reverse_iterator                 = typename underling_matrix_type::reverse_column_iterator;
    using const_reverse_iterator           = typename underling_matrix_type::const_reverse_column_iterator;
    using transpose_type                   = typename underling_matrix_type::row_type;
    using transpose_view                   = typename underling_matrix_type::row_view;
    using const_transpose_view             = typename underling_matrix_type::const_row_view;
    using transpose_iterator               = typename underling_matrix_type::row_iterator;
    using const_transpose_iterator         = typename underling_matrix_type::const_row_iterator;
    using reverse_transpose_iterator       = typename underling_matrix_type::reverse_row_iterator;
    using const_reverse_transpose_iterator = typename underling_matrix_type::const_reverse_row_iterator;
    using column_type                      = typename underling_matrix_type::column_type;
    using column_view                      = typename underling_matrix_type::column_view;
    using const_column_view                = typename underling_matrix_type::const_column_view;
    using column_iterator                  = typename underling_matrix_type::column_iterator;
    using const_column_iterator            = typename underling_matrix_type::const_column_iterator;
    using reverse_column_iterator          = typename underling_matrix_type::reverse_column_iterator;
    using const_reverse_column_iterator    = typename underling_matrix_type::const_reverse_column_iterator;
    using row_type                         = typename underling_matrix_type::value_type;
    using row_view                         = typename underling_matrix_type::reference;
    using const_row_view                   = typename underling_matrix_type::const_reference;
    using row_iterator                     = typename underling_matrix_type::iterator;
    using const_row_iterator               = typename underling_matrix_type::const_iterator;
    using reverse_row_iterator             = typename underling_matrix_type::reverse_iterator;
    using const_reverse_row_iterator       = typename underling_matrix_type::const_reverse_iterator;
    using diagonal_iterator                = typename underling_matrix_type::diagonal_iterator;
    using const_diagonal_iterator          = typename underling_matrix_type::const_diagonal_iterator;
    using reverse_diagonal_iterator        = typename underling_matrix_type::reverse_diagonal_iterator;
    using const_reverse_diagonal_iterator  = typename underling_matrix_type::const_reverse_diagonal_iterator;

    std::reference_wrapper<underling_matrix_type> _base;
    size_type                                     _index;
};

template <class underling_matrix_type>
struct _matrix_view_data<underling_matrix_type, _matrix_space::ROW>
{
  protected:
    using size_type                        = typename underling_matrix_type::size_type;
    using difference_type                  = typename underling_matrix_type::difference_type;
    using value_type                       = typename underling_matrix_type::value_type;
    using reference                        = typename underling_matrix_type::reference;
    using const_reference                  = typename underling_matrix_type::const_reference;
    using pointer                          = typename underling_matrix_type::pointer;
    using const_pointer                    = typename underling_matrix_type::const_pointer;
    using matrix_type                      = typename underling_matrix_type::row_type;
    using matrix_view                      = typename underling_matrix_type::row_view;
    using const_matrix_view                = typename underling_matrix_type::const_row_view;
    using iterator                         = typename underling_matrix_type::row_iterator;
    using const_iterator                   = typename underling_matrix_type::const_row_iterator;
    using reverse_iterator                 = typename underling_matrix_type::reverse_row_iterator;
    using const_reverse_iterator           = typename underling_matrix_type::const_reverse_row_iterator;
    using transpose_type                   = typename underling_matrix_type::column_type;
    using transpose_view                   = typename underling_matrix_type::column_view;
    using const_transpose_view             = typename underling_matrix_type::const_column_view;
    using transpose_iterator               = typename underling_matrix_type::column_iterator;
    using const_transpose_iterator         = typename underling_matrix_type::const_column_iterator;
    using reverse_transpose_iterator       = typename underling_matrix_type::reverse_column_iterator;
    using const_reverse_transpose_iterator = typename underling_matrix_type::const_reverse_column_iterator;
    using column_type                      = typename underling_matrix_type::value_type;
    using column_view                      = typename underling_matrix_type::reference;
    using const_column_view                = typename underling_matrix_type::const_reference;
    using column_iterator                  = typename underling_matrix_type::iterator;
    using const_column_iterator            = typename underling_matrix_type::const_iterator;
    using reverse_column_iterator          = typename underling_matrix_type::reverse_iterator;
    using const_reverse_column_iterator    = typename underling_matrix_type::const_reverse_iterator;
    using row_type                         = typename underling_matrix_type::row_type;
    using row_view                         = typename underling_matrix_type::row_view;
    using const_row_view                   = typename underling_matrix_type::const_row_view;
    using row_iterator                     = typename underling_matrix_type::row_iterator;
    using const_row_iterator               = typename underling_matrix_type::const_row_iterator;
    using reverse_row_iterator             = typename underling_matrix_type::reverse_row_iterator;
    using const_reverse_row_iterator       = typename underling_matrix_type::const_reverse_row_iterator;
    using diagonal_iterator                = typename underling_matrix_type::diagonal_iterator;
    using const_diagonal_iterator          = typename underling_matrix_type::const_diagonal_iterator;
    using reverse_diagonal_iterator        = typename underling_matrix_type::reverse_diagonal_iterator;
    using const_reverse_diagonal_iterator  = typename underling_matrix_type::const_reverse_diagonal_iterator;

    std::reference_wrapper<underling_matrix_type> _base;
    size_type                                     _index;
};
}