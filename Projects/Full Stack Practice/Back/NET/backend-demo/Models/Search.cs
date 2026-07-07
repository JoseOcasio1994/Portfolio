using Microsoft.Extensions.Hosting;
using NuGet.Protocol;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Diagnostics.CodeAnalysis;

namespace backend_demo.Models;

public class Search
{
    public int? PageNumber { get; set; }
    public int? PageSize { get; set; }
    public string? Sort { get; set; }
    public string? Filter { get; set; }

    public Search() { }

    public Search(Search other)
    {
        this.PageNumber = other.PageNumber ?? 1;
        this.PageSize = other.PageSize ?? 10;
        this.Sort = other.Sort ?? "Name";
        this.Filter = other.Filter ?? String.Empty;
    }
}

public class SearchResults<T>
{
    public IEnumerable<T>? Results { get; set; }
    public int? CurrentPage { get; set; }
    public int? TotalPages { get; set; }
    public int? TotalCount { get; set; }

    public SearchResults(IEnumerable<T> results, int curPage, int totalPages, int count) {
        this.Results = results;
        this.CurrentPage = curPage;
        this.TotalPages = totalPages;
        this.TotalCount = count;
    }
}